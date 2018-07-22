#include "player.h"
#include "subPlayer.h"
#include "ball.h"
#include "../event/eventListener.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../gameSys/level/level.h"
#include "../gameSys/level/zone.h"
#include "../gameSys/bar/energyBar.h"
#include "../gameSys/skill/playerSkill.h"
#include "../gameSys/skill/ballSkill.h"
#include "../manager/audioManager.h"
#include "../manager/textureManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace game;

// player model file
std::map<Player::Model, Player::BoardFile> Player::modelFileNames({
		
	});

Player::Player(const std::shared_ptr<Level> level)
	: bFlash(false)
	, bFlashCD(false)
	, fSpeed(4.5f)
	, energyBar(new EnergyBar(100, false, false, false))
	, key(new ControlKey)
	, autoUse({ std::pair(SkillSelect::_Ball, false), std::pair(SkillSelect::_Player, false) })
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
				std::pair(Effect::Sturdy, false) 
			})
		, std::vector<Attribute::Kind>({ Attribute::None })
		, true, energyBar, this)
		, std::make_shared<PlayerSkill>(
		PlayerSkill::DropRateUp, sf::seconds(30)
		, std::vector<std::pair<Effect::Kind, bool>>({ 
				std::pair(Effect::Fragile, true)
			})
		, std::vector<Attribute::Kind>({ Attribute::None })
		, true, energyBar, this)
	};
	// set ball skill
	defender.ballSkills = {
	};
	// set player zone
	Zone::getInstance().settleZone(Zone::Player, sf::Vector2f(0.0f, LEVEL_HEIGHT - 100.f), 100.f);
	addChild({ std::dynamic_pointer_cast<sf::Drawable>(defender.board)
		, std::dynamic_pointer_cast<sf::Drawable>(defender.absorbEngine)
		, std::dynamic_pointer_cast<sf::Drawable>(defender.hitLight) });
	// add child
	/*std::for_each(defender.ballSkills.begin(), defender.ballSkills.end()
		, [&](const std::shared_ptr<BallSkill> & skill) {
		skill->initialize();
		addChild({ skill });
	});
	std::for_each(defender.playerSkills.begin(), defender.playerSkills.end()
		, [&](const std::shared_ptr<PlayerSkill> & skill) {
		skill->initialize();
		addChild({ skill });
	});*/
	// add listener
	addListener(std::make_shared<EventListener<GameStartedEvent>>([this](auto & event) { onGameStarted(event); }));
	addListener(std::make_shared<EventListener<GameReadyEvent>>([this](auto & event) { onGameReady(event); }));
	addListener(std::make_shared<EventListener<GameFinishedLevelEvent>>([this](auto & event) { onGameFinishedLevel(event); }));
	addListener(std::make_shared<EventListener<KeyPressedEvent>>([this](auto & event) { onkeyPressed(event); }));
	addListener(std::make_shared<EventListener<MousePressedEvent>>([this](auto & event) { onMousePressed(event); }));
}

void Player::update(const float updateRatio) {
	const Vector2f &mainBallPos(m_ball->getMainBallPosition());
	const float mainBallRadius = m_ball->getMainBallRadius();
	const FloatRect playerBoardBound = defender.board->getGlobalBounds();
	if (playerBoardBound.left >= 0
		&& (Keyboard::isKeyPressed(key->leftMove))) {
		defender.board->move(Vector2f(-fSpeed / SLICE * updateRatio, 0));
		defender.hitLight->move(Vector2f(-fSpeed / SLICE * updateRatio, 0));
	}
	if (playerBoardBound.left + playerBoardBound.width <= LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(key->rightMove))) {
		defender.board->move(Vector2f(fSpeed / SLICE * updateRatio, 0));
		defender.hitLight->move(Vector2f(fSpeed / SLICE * updateRatio, 0));
	}
	defender.absorbEngine->setPosition(defender.board->getPosition());
}

void Player::setPlayerControlKey(const sf::Keyboard::Key leftMove, const sf::Keyboard::Key rightMove
	, const sf::Keyboard::Key shot, const sf::Keyboard::Key playerSkill
	, const sf::Keyboard::Key playerSkillSwap, const sf::Keyboard::Key ballSkill
	, const sf::Keyboard::Key ballSkillSwap, const sf::Keyboard::Key switchToPrevChargingSkill
	, const sf::Keyboard::Key switchToNextChargingSkill) {
	key->leftMove = leftMove;
	key->rightMove = rightMove;
	key->shot = shot;
	key->ballSkill = ballSkill;
	key->ballSkillSwap = ballSkillSwap;
	key->playerSkill = playerSkill;
	key->playerSkillSwap = playerSkillSwap;
	key->switchToPrevChargingSkill = switchToPrevChargingSkill;
	key->switchToNextChargingSkill = switchToNextChargingSkill;
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
		defender.board->setFillColor(Color::White);
		defender.absorbEngine->setFillColor(Color::White);
		defender.hitLight->setFillColor(Color::Transparent);
		auto boardTexture = TextureManager::getInstance().get(modelFileNames[model].board);
		auto absorbEngineTexture = TextureManager::getInstance().get(modelFileNames[model].absorbEngine);
		auto hitLightTexture = TextureManager::getInstance().get(modelFileNames[model].hitLight);
		defender.board->setTexture(boardTexture);
		defender.absorbEngine->setTexture(absorbEngineTexture);
		defender.hitLight->setTexture(hitLightTexture);
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

void Player::setAutoUse(const SkillSelect skill, const bool isAutoUse) {
	autoUse[skill] = isAutoUse;
}

void Player::resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer
	, const std::shared_ptr<Ball> ball) {
	c_subPlayer = std::move(subPlayer);
	m_ball = std::move(ball);
}

float Player::getSpeed() const {
	return fSpeed;
}

bool Player::isAutoUse(const SkillSelect select) const {
	return autoUse.at(select);
}

const Vector2f & Player::getPosition() const {
	return defender.board->getPosition();
}

const Player::ControlKey & Player::getKey() const {
	return *key;
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
		key->leftMove = Key::Left;
		key->rightMove = Key::Right;
		key->shot = Key::G;
		key->ballSkill = Key::D;
		key->ballSkillSwap = Key::E;
		key->playerSkill = Key::F;
		key->playerSkillSwap = Key::R;
		key->switchToPrevChargingSkill = Key::Up;
		key->switchToNextChargingSkill = Key::Down;
	}
	else {
		key->leftMove = Key::Left;
		key->rightMove = Key::Right;
		key->shot = Key::Unknown;
		key->ballSkill = Key::Unknown;
		key->ballSkillSwap = Key::Unknown;
		key->playerSkill = Key::Unknown;
		key->playerSkillSwap = Key::Unknown;
		key->switchToPrevChargingSkill = Key::Up;
		key->switchToNextChargingSkill = Key::Down;
	}
}

void Player::onGameStarted(GameStartedEvent & event) {
	const Vector2f &mainBallPos(m_ball->getMainBallPosition());
	const float mainBallRadius = m_ball->getMainBallRadius();
	flashRange(mainBallPos, mainBallRadius);
	if (bFlash) {
		flashElapsed();
	}
	// update skills
	/*std::for_each(defender.playerSkills.begin(), defender.playerSkills.end()
		, [&](const std::shared_ptr<PlayerSkill> & skill) {
		assert(skill->isInitialize());
		skill->update();
	});
	std::for_each(defender.ballSkills.begin(), defender.ballSkills.end()
		, [&](const std::shared_ptr<BallSkill> & skill) {
		assert(skill->isInitialize());
		skill->update();
	});*/
	dispatchAllChildrenEvent(event);
}

void Player::onGameReady(GameReadyEvent & event) {
	resetFlash();
}

void Player::onGameFinishedLevel(GameFinishedLevelEvent & event) {
	dispatchAllChildrenEvent(event);
}

void Player::onkeyPressed(KeyPressedEvent & event) {
	dispatchAllChildrenEvent(event);
}

void Player::onMousePressed(MousePressedEvent & event) {
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

void Player::resetFlash() {
	bFlash = false;
	bFlashCD = false;
	setFlashFillColor(Color(defender.hitLight->getFillColor().r
		, defender.hitLight->getFillColor().b
		, defender.hitLight->getFillColor().g
		, Color::Transparent.a));
}

void Player::flashRange(const Vector2f ballPos, const float radius) {
	const FloatRect playerBounds = getGlobalBounds();
	const FloatRect hitLightBounds = defender.hitLight->getGlobalBounds();
	const Vector2f pos1P = getPosition();

	if (!bFlashCD) {
		if (m_ball->isMainBallIntersect(playerBounds)) {
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
