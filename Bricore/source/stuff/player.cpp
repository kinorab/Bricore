#include "player.h"
#include "subPlayer.h"
#include "ball.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../definition/intersects.h"
#include "../gameSys/level/level.h"
#include "../gameSys/level/area/zone.h"
#include "../gameSys/bar/energyBar.h"
#include "../gameSys/skill/playerSkill.h"
#include "../gameSys/skill/ballSkill.h"
#include "../manager/audioManager.h"
#include "../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace game;

Player::Player(const std::shared_ptr<Level> level)
	: bFlash(false)
	, bFlashCD(false)
	, fSpeed(4.5f)
	, energyBar(new EnergyBar(100, false, false, false))
	, key()
	, m_level(level) {
	// set fundamental size setting
	defender.board.reset(new RectangleShape(Vector2f(240.f, 12.f)));
	defender.absorbEngine.reset(new RectangleShape(Vector2f(defender.board->getSize().x * 0.1f
		, defender.board->getSize().y)));
	defender.hitLight.reset(new RectangleShape(Vector2f(defender.board->getSize().x * 0.05f
		, defender.board->getSize().y)));
	defender.board->setOrigin(Vector2f(defender.board->getSize().x / 2
		, defender.board->getSize().y / 2));
	defender.board->setPosition(Vector2f(LEVEL_WIDTH / 2
		, LEVEL_HEIGHT - defender.board->getSize().y));
	defender.absorbEngine->setOrigin(Vector2f(defender.absorbEngine->getSize().x / 2
		, defender.absorbEngine->getSize().y / 2));
	defender.absorbEngine->setPosition(defender.board->getPosition());
	defender.hitLight->setOrigin(Vector2f(defender.hitLight->getSize().x / 2
		, defender.hitLight->getSize().y / 2));
	defender.hitLight->setPosition(defender.board->getPosition());
	// set default key setting
	defaultKeySettle();
	// set default model setting
	changeModel(Classic);
	// set player skill
	defender.playerSkills = {
		std::make_shared<PlayerSkill>(
		PlayerSkill::AmbitGuard, sf::seconds(8)
		, std::vector<std::pair<Effect::Kind, bool>>({ 
				std::pair(Effect::Invincible, false)
				, std::pair(Effect::Sturdy, false) 
			})
		, std::vector<Attribute::Kind>({ Attribute::None })
		, false, true, energyBar)
		, std::make_shared<PlayerSkill>(
		PlayerSkill::DropRateUp, sf::seconds(30)
		, std::vector<std::pair<Effect::Kind, bool>>({ 
				std::pair(Effect::None, true)
			})
		, std::vector<Attribute::Kind>({ Attribute::None })
		, false, true, energyBar)
	};
	// set ball skill
	defender.ballSkills = {
	};
	// set player zone
	using namespace game;
	Zone::getInstance().settleZone(Zone::Player, sf::Vector2f(0.0f, LEVEL_HEIGHT - 100.f), 100.f);
	addChild({ defender.board, defender.absorbEngine, defender.hitLight });
	std::for_each(defender.ballSkills.begin(), defender.ballSkills.end()
		, [&](const std::shared_ptr<BallSkill> & skill) {
		skill->initialize();
		addChild({ skill });
	});
	std::for_each(defender.playerSkills.begin(), defender.playerSkills.end()
		, [&](const std::shared_ptr<PlayerSkill> & skill) {
		skill->initialize();
		addChild({ skill });
	});
}

void Player::update(const float updateRatio) {
	const Vector2f &mainBallPos(m_ball->getMainBallPosition());
	const float mainBallRadius = m_ball->getMainBallRadius();
	const FloatRect playerBoardBound = defender.board->getGlobalBounds();
	// update skills
	std::for_each(defender.playerSkills.begin(), defender.playerSkills.end()
		, [&](const std::shared_ptr<PlayerSkill> & skill) {
		assert(skill->isInitialize());
		skill->update();
	});
	std::for_each(defender.ballSkills.begin(), defender.ballSkills.end()
		, [&](const std::shared_ptr<BallSkill> & skill) {
		assert(skill->isInitialize());
		skill->update();
	});
	// update player
	if (playerBoardBound.left >= 0
		&& (Keyboard::isKeyPressed(key.leftMove))
		) {
		defender.board->move(Vector2f(-fSpeed / SLICE * updateRatio, 0));
		defender.hitLight->move(Vector2f(-fSpeed / SLICE * updateRatio, 0));
	}
	if (playerBoardBound.left + playerBoardBound.width <= LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(key.rightMove))
		) {
		defender.board->move(Vector2f(fSpeed / SLICE * updateRatio, 0));
		defender.hitLight->move(Vector2f(fSpeed / SLICE * updateRatio, 0));
	}
	if (currentGameState == GameState::STARTED) {
		flashRange(mainBallPos, mainBallRadius);
	}
	if (bFlash) {
		flashElapsed();
	}
	defender.absorbEngine->setPosition(defender.board->getPosition());
}

void Player::setPlayerControlKey(const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
	, const sf::Keyboard::Key shot, const sf::Keyboard::Key playerSkill
	, const sf::Keyboard::Key playerSkillSwap, const sf::Keyboard::Key ballSkill
	, const sf::Keyboard::Key ballSkillSwap, const sf::Keyboard::Key switchToPrevChargingSkill
	, const sf::Keyboard::Key switchToNextChargingSkill) {
	key = ControlKey{ leftMove, rightMove, shot };
	PlayerSkill::resetKey(playerSkill, playerSkillSwap, switchToPrevChargingSkill, switchToNextChargingSkill);
	BallSkill::resetKey(ballSkill, ballSkillSwap);
}

void Player::loadPlayerModelPreview(const std::map<Model, BoardFile> & fileName, const bool isSmooth) {
	std::for_each(fileName.begin(), fileName.end(), [&](const std::pair<Model, BoardFile> & file) {
		modelPreviews.emplace(file.first, new BoardTexture);
		modelPreviews[file.first]->board.reset(TextureManager::getInstance().get(file.second.board));
		modelPreviews[file.first]->absorbEngine.reset(TextureManager::getInstance().get(file.second.absorbEngine));
		modelPreviews[file.first]->hitLight.reset(TextureManager::getInstance().get(file.second.hitLight));
		modelPreviews[file.first]->board->setSmooth(isSmooth);
		modelPreviews[file.first]->absorbEngine->setSmooth(isSmooth);
		modelPreviews[file.first]->hitLight->setSmooth(isSmooth);
	});
}

void Player::changeModel(const Model model) {
	// set defender context
	if (model == Classic) {
		defender.board->setTexture(nullptr);
		defender.absorbEngine->setTexture(nullptr);
		defender.hitLight->setTexture(nullptr);
		defender.board->setFillColor(Color::Green);
		defender.absorbEngine->setFillColor(Color::Yellow);
		defender.hitLight->setFillColor(Color(Color::Red.r, Color::Red.b, Color::Red.g, Color::Transparent.a));
	}
	else {
		defender.board->setFillColor(Color::Transparent);
		defender.absorbEngine->setFillColor(Color::Transparent);
		defender.hitLight->setFillColor(Color::Transparent);
		defender.board->setTexture(modelPreviews[model]->board.get());
		defender.absorbEngine->setTexture(modelPreviews[model]->absorbEngine.get());
		defender.hitLight->setTexture(modelPreviews[model]->hitLight.get());
	}
	// set defender model
	defender.currentModel = model;
}

void Player::addPlayerSkill(PlayerSkill && playerSkill) {
	defender.playerSkills.push_back(std::make_shared<PlayerSkill>(playerSkill));
}

void Player::addBallSkill(BallSkill && ballSkill) {
	defender.ballSkills.push_back(std::make_shared<BallSkill>(ballSkill));
}

void Player::setAutoUse(const SkillChoose skill, const bool autoUse) {
	switch (skill) {
	case SkillChoose::_Ball:
		std::for_each(defender.ballSkills.begin(), defender.ballSkills.end()
			, [=](const std::shared_ptr<BallSkill> & skill) {
			skill->setAutoUse(autoUse);
		});
		break;
	case SkillChoose::_Player:
		std::for_each(defender.playerSkills.begin(), defender.playerSkills.end()
			, [=](const std::shared_ptr<PlayerSkill> & skill) {
			skill->setAutoUse(autoUse);
		});
		break;
	default:
		throw std::invalid_argument("Invalid skill kind.");
	}
}

void Player::resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer
	, const std::shared_ptr<Ball> ball) {
	c_subPlayer = std::move(subPlayer);
	m_ball = std::move(ball);
}

float Player::getSpeed() const {
	return fSpeed;
}

const Vector2f & Player::getPosition() const {
	return defender.board->getPosition();
}

Vector2f Player::getTopCenterPos() const {
	return Vector2f(defender.board->getPosition().x, defender.board->getGlobalBounds().top);
}

FloatRect Player::getGlobalBounds() const {
	return defender.board->getGlobalBounds();
}

sys::DPointf Player::getDP() const {
	return sys::DPointf(defender.board->getGlobalBounds());
}

Player::Model Player::getModel() const {
	return defender.currentModel;
}

Player::~Player() {
	removeAllChildren(true);
	removeAllListener();
}

void Player::draw(RenderTarget &target, RenderStates states) const {
	Container::draw(target, states);
}

void Player::defaultKeySettle() {
	using Key = sf::Keyboard::Key;
	if (m_level->isDefaultControlKeySettled()) return;
	if (m_level->getMode() == Mode::_1Player) {
		key = ControlKey{ Key::Left, Key::Right, Key::G };
		PlayerSkill::resetKey(Key::F, Key::R, Key::Up, Key::Down);
		BallSkill::resetKey(Key::D, Key::E);
	}
	else {
		key = ControlKey{ Key::Left, Key::Right, Key::Unknown };
		PlayerSkill::resetKey(Key::Unknown, Key::Unknown, Key::Up, Key::Down);
		BallSkill::resetKey(Key::Unknown, Key::Unknown);
	}
}

void Player::setFlashPosition(const Vector2f & position) {
	defender.hitLight->setPosition(position);
}

void Player::setFlashFillColor(const sf::Color & color) {
	defender.hitLight->setFillColor(color);
}

void Player::flashElapsed() {
	const float time = static_cast<float>(elapsed.getElapsedTime().asMilliseconds());
	if (time <= 1500.f) {
		const float rate = (1.f - time / 1500.f);
		setFlashFillColor(Color(defender.hitLight->getFillColor().r
			, defender.hitLight->getFillColor().b
			, defender.hitLight->getFillColor().g
			, static_cast<Uint8>(rate * 255)));
	}
	else {
		bFlash = false;
	}
}

void Player::flashRange(const Vector2f ballPos, const float radius) {
	const FloatRect playerBounds = getGlobalBounds();
	const FloatRect hitLightBounds = defender.hitLight->getGlobalBounds();
	const Vector2f pos1P = getPosition();

	if (!bFlashCD) {
		if (sys::ballRectINCIntersects(ballPos, radius, playerBounds)) {
			elapsed.restart();
			AudioManager::getInstance().getSound("hitBoard")->play();
			if (ballPos.x - radius <= playerBounds.left) {
				setFlashPosition(Vector2f(playerBounds.left + hitLightBounds.width / 2, pos1P.y));
			}
			else if (ballPos.x + radius >= playerBounds.left + playerBounds.width) {
				setFlashPosition(Vector2f(playerBounds.left + playerBounds.width - hitLightBounds.width / 2, pos1P.y));
			}
			else {
				setFlashPosition(Vector2f(ballPos.x, pos1P.y));
			}
			bFlash = true;
			bFlashCD = true;
			CDTime.restart();
		}
	}
	else if (CDTime.getElapsedTime().asSeconds() > 0.25f) {
		bFlashCD = false;
	}
}
