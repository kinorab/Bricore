#include "player.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../definition/intersects.h"
#include "../gameSys/area/area.h"
#include "../manager/audioManager.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Player::Player()
	: board(RectangleShape(Vector2f(240.f, 12.f)))
	, yellowRange(RectangleShape(Vector2f(board.getSize().x * 0.1f, board.getSize().y)))
	, redRange(RectangleShape(Vector2f(board.getSize().x * 0.05f, board.getSize().y)))
	, flash(false)
	, flashCD(false)
	, speed(4.5f)
	, leftMoveKey(sf::Keyboard::Left)
	, rightMoveKey(sf::Keyboard::Right) {
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
	Area::getInstance().settleArea(Area::Player, sf::Vector2f(0.0f, LEVEL_HEIGHT - 100.f), 100.f);
}

void Player::update(const Vector2f &ballPos, const float ballRadius, const float updateRatio) {
	const FloatRect playerBound = board.getGlobalBounds();
	if (playerBound.left >= 0
		&& (Keyboard::isKeyPressed(leftMoveKey))
		) {
		board.move(Vector2f(-speed / SLICE * updateRatio, 0));
		redRange.move(Vector2f(-speed / SLICE * updateRatio, 0));
	}
	if (playerBound.left + playerBound.width <= LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(rightMoveKey))
		) {
		board.move(Vector2f(speed / SLICE * updateRatio, 0));
		redRange.move(Vector2f(speed / SLICE * updateRatio, 0));
	}
	if (game::currentState == GameState::STARTED) {
		flashRange(AudioManager::getInstance().sound1, ballPos, ballRadius);
	}
	if (flash) {
		flashElapsed();
	}
	yellowRange.setPosition(board.getPosition());
}

void Player::setPlayerKey(const Keyboard::Key left, const Keyboard::Key right) {
	leftMoveKey = left;
	rightMoveKey = right;
}

float Player::getSpeed() const {
	return speed;
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

Player::~Player(){ }

void Player::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();
	target.draw(board, states);
	target.draw(yellowRange, states);
	target.draw(redRange, states);
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
		flash = false;
	}
}

void Player::flashRange(Sound & sound, const Vector2f ballPos, const float radius) {
	const FloatRect playerBounds = getGlobalBounds();
	const FloatRect rangeBounds = redRange.getGlobalBounds();
	const Vector2f pos1P = getPosition();

	if (!flashCD) {
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
			flash = true;
			flashCD = true;
			CDTime.restart();
		}
	}
	else if (CDTime.getElapsedTime().asSeconds() > 0.25f) {
		flashCD = false;
	}
}
