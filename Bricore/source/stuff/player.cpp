#include "player.h"
#include "subPlayer.h"
#include "ball.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../definition/intersects.h"
#include "../gameSys/area/zone.h"
#include "../gameSys/level/level.h"
#include "../gameSys/bar/energyBar.h"
#include "../gameSys/skill/playerSkill.h"
#include "../gameSys/skill/ballSkill.h"
#include "../manager/audioManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace game;

Player::Player(const std::shared_ptr<Level> level)
	: board(RectangleShape(Vector2f(240.f, 12.f)))
	, yellowRange(RectangleShape(Vector2f(board.getSize().x * 0.1f, board.getSize().y)))
	, redRange(RectangleShape(Vector2f(board.getSize().x * 0.05f, board.getSize().y)))
	, bFlash(false)
	, bFlashCD(false)
	, fSpeed(4.5f)
	, energyBar(new EnergyBar(100, false, false, false))
	, m_level(level) {
	defaultKeySettle();
	playerSkills = {
		std::make_shared<PlayerSkill>(
		PlayerSkill::AmbitGuard, sf::seconds(8)
		, std::vector<Effect::Kind>({ Effect::Invincible, Effect::Sturdy })
		, std::vector<Attribute::Kind>({ Attribute::None })
		, false, true, energyBar)
		, std::make_shared<PlayerSkill>(
		PlayerSkill::DropRateUp, sf::seconds(30)
		, std::vector<Effect::Kind>({ Effect::None })
		, std::vector<Attribute::Kind>({ Attribute::None })
		, false, true, energyBar)
	};
	ballSkills = {
	};
	board.setOrigin(Vector2f(board.getSize().x / 2, board.getSize().y / 2));
	board.setFillColor(Color::Green);
	board.setPosition(Vector2f(LEVEL_WIDTH / 2, LEVEL_HEIGHT - board.getSize().y));
	yellowRange.setOrigin(Vector2f(yellowRange.getSize().x / 2, yellowRange.getSize().y / 2));
	yellowRange.setPosition(board.getPosition());
	yellowRange.setFillColor(Color::Yellow);
	redRange.setOrigin(Vector2f(redRange.getSize().x / 2, redRange.getSize().y / 2));
	redRange.setPosition(board.getPosition());
	redRange.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0)));
	using namespace game;
	Zone::getInstance().settleZone(Zone::Player, sf::Vector2f(0.0f, LEVEL_HEIGHT - 100.f), 100.f);
	std::for_each(playerSkills.begin(), playerSkills.end()
		, [&](const std::shared_ptr<PlayerSkill> & skill) {
		skill->initialize();
	});
	std::for_each(ballSkills.begin(), ballSkills.end()
		, [&](const std::shared_ptr<BallSkill> & skill) {
		skill->initialize();
	});
}

void Player::update(const float updateRatio) {
	const Vector2f &mainBallPos{ m_ball->getMainBallPosition() };
	const float mainBallRadius = m_ball->getMainBallRadius();
	const FloatRect playerBound = board.getGlobalBounds();
	if (playerBound.left >= 0
		&& (Keyboard::isKeyPressed(key.leftMove))
		) {
		board.move(Vector2f(-fSpeed / SLICE * updateRatio, 0));
		redRange.move(Vector2f(-fSpeed / SLICE * updateRatio, 0));
	}
	if (playerBound.left + playerBound.width <= LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(key.rightMove))
		) {
		board.move(Vector2f(fSpeed / SLICE * updateRatio, 0));
		redRange.move(Vector2f(fSpeed / SLICE * updateRatio, 0));
	}
	if (currentState == GameState::STARTED) {
		flashRange(AudioManager::getInstance().sound1, mainBallPos, mainBallRadius);
	}
	if (bFlash) {
		flashElapsed();
	}
	yellowRange.setPosition(board.getPosition());
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

void Player::resetCopyTarget(const std::shared_ptr<const SubPlayer> subPlayer
	, const std::shared_ptr<Ball> ball) {
	c_subPlayer = std::move(subPlayer);
	m_ball = std::move(ball);
}

void Player::handle(const sf::Event & event) {
	std::for_each(playerSkills.begin(), playerSkills.end()
		, [&](const std::shared_ptr<PlayerSkill> & skill) {
		assert(skill->isInitialize());
		skill->handleSkill(&event);
		skill->handleSelect(&event);
	});
	std::for_each(ballSkills.begin(), ballSkills.end()
		, [&](const std::shared_ptr<BallSkill> & skill) {
		assert(skill->isInitialize());
		skill->handleSkill(&event);
		skill->handleSelect(&event);
	});
}

float Player::getSpeed() const {
	return fSpeed;
}

const Vector2f & Player::getPosition() const {
	return board.getPosition();
}

Vector2f Player::getTopCenterPos() const {
	return Vector2f(board.getPosition().x, board.getGlobalBounds().top);
}

FloatRect Player::getGlobalBounds() const {
	return board.getGlobalBounds();
}

sys::DPointf Player::getDP() const {
	return sys::DPointf(board.getGlobalBounds());
}

Player::~Player() { }

void Player::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();
	target.draw(board, states);
	target.draw(yellowRange, states);
	target.draw(redRange, states);
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
	redRange.setPosition(position);
}

void Player::setFlashFillColor(const sf::Color & color) {
	redRange.setFillColor(color);
}

void Player::flashElapsed() {
	const float time = static_cast<float>(elapsed.getElapsedTime().asMilliseconds());
	if (time <= 1500.f) {
		const float rate = (1.f - time / 1500.f);
		setFlashFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(rate * 255)));
	}
	else {
		bFlash = false;
	}
}

void Player::flashRange(Sound & sound, const Vector2f ballPos, const float radius) {
	const FloatRect playerBounds = getGlobalBounds();
	const FloatRect rangeBounds = redRange.getGlobalBounds();
	const Vector2f pos1P = getPosition();

	if (!bFlashCD) {
		if (sys::ballRectINCIntersects(ballPos, radius, playerBounds)) {
			elapsed.restart();
			sound.play();
			if (ballPos.x - radius <= playerBounds.left) {
				setFlashPosition(Vector2f(playerBounds.left + rangeBounds.width / 2, pos1P.y));
			}
			else if (ballPos.x + radius >= playerBounds.left + playerBounds.width) {
				setFlashPosition(Vector2f(playerBounds.left + playerBounds.width - rangeBounds.width / 2, pos1P.y));
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
