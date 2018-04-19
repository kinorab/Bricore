#include "player.h"
#include "define.h"
#include "intersects.h"
#include <iostream>

using namespace sf;

bool Player::flash = false;
Clock Player::elapsed;
RectangleShape Player::mainPlayer(Vector2f(240, 12));
//RectangleShape Player::subPlayer(Vector2f(50, 50));
RectangleShape Player::yellowRange(Vector2f(mainPlayer.getSize().x * 0.1f, mainPlayer.getSize().y));
RectangleShape Player::redRange(Vector2f(yellowRange.getSize().x / 2, mainPlayer.getSize().y));
RectangleShape Player::playerArea(Vector2f(LEVEL_WIDTH, 100.f));
std::mutex Player::mutex;
std::shared_ptr<Player> Player::instance = nullptr;

Player::Player() {
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(LEVEL_WIDTH / 2, LEVEL_HEIGHT - mainPlayer.getSize().y));
	yellowRange.setOrigin(Vector2f(yellowRange.getSize().x / 2, yellowRange.getSize().y / 2));
	yellowRange.setPosition(mainPlayer.getPosition());
	yellowRange.setFillColor(Color::Yellow);
	redRange.setOrigin(Vector2f(redRange.getSize().x / 2, redRange.getSize().y / 2));
	redRange.setPosition(mainPlayer.getPosition());
	redRange.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0)));
	playerArea.setPosition(0.0f, LEVEL_HEIGHT - 100.f);
}

std::shared_ptr<Player> Player::getInstance() {
	std::shared_ptr<Player> playerPtr = std::atomic_load_explicit(&instance, std::memory_order_acquire);
	if (!playerPtr) {
		// prevent multithread get instance
		std::lock_guard<std::mutex> lock(mutex);
		playerPtr = std::atomic_load_explicit(&instance, std::memory_order_relaxed);
		if (!playerPtr) {
			playerPtr = std::shared_ptr<Player>(new Player());
			std::atomic_store_explicit(&instance, playerPtr, std::memory_order_release);
		}
	}
	return playerPtr;
}

void Player::playerMove(Sound &sound, const Vector2f ballPos, const float radius) {
	FloatRect playerBound = mainPlayer.getGlobalBounds();
	if (playerBound.left >= 0
		&& (Keyboard::isKeyPressed(Keyboard::Left))
		) {
		mainPlayer.move(Vector2f(-MAINPLAYERSPEED / SLICE, 0));
		redRange.move(Vector2f(-MAINPLAYERSPEED / SLICE, 0));
	}
	if (playerBound.left + playerBound.width <= LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(Keyboard::Right))
		) {
		mainPlayer.move(Vector2f(MAINPLAYERSPEED / SLICE, 0));
		redRange.move(Vector2f(MAINPLAYERSPEED / SLICE, 0));
	}
	if (GameState::start) {
		flashRange(sound, ballPos, radius);
	}
	if (flash) {
		flashElapsed();
	}

	yellowRange.setPosition(mainPlayer.getPosition());
}

const Vector2f & Player::getMainPlayerPos() {
	return mainPlayer.getPosition();
}

const Vector2f Player::getMainPlayerTopCenterPos() {
	return Vector2f(mainPlayer.getPosition().x, mainPlayer.getGlobalBounds().top);
}

const FloatRect Player::getMainPlayerBounds() {
	return mainPlayer.getGlobalBounds();
}

const sys::DPointf Player::getMainPlayerDP() {
	const Vector2f LT(mainPlayer.getGlobalBounds().left, mainPlayer.getGlobalBounds().top);
	const Vector2f RB(mainPlayer.getGlobalBounds().left + mainPlayer.getGlobalBounds().width
		, mainPlayer.getGlobalBounds().top + mainPlayer.getGlobalBounds().height);
	return sys::DPointf(LT, RB);
}

const sys::DPointf Player::getPlayerAreaDP() {
	const Vector2f LT(playerArea.getGlobalBounds().left, playerArea.getGlobalBounds().top);
	const Vector2f RB(LT.x + playerArea.getGlobalBounds().width, LT.y + playerArea.getGlobalBounds().height);
	return sys::DPointf(LT, RB);
}

void Player::draw(RenderTarget &target, RenderStates states) const {
	states.texture = nullptr;
	target.draw(mainPlayer, states);
	target.draw(yellowRange, states);
	target.draw(redRange, states);
}

void Player::setFlashPosition(const Vector2f & position) {
	redRange.setPosition(position);
}

void Player::setFlashPosition(const float posX, const float posY) {
	redRange.setPosition(posX, posY);
}

void Player::setFlashFillColor(const sf::Color & color) {
	redRange.setFillColor(color);
}

void Player::flashElapsed() {
	float time = static_cast<float>(elapsed.getElapsedTime().asMilliseconds());
	if (time <= 1500.f) {
		float rate = (1.f - time / 1500.f);
		setFlashFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(rate * 255)));
	}
	else {
		flash = false;
	}
}

void Player::flashRange(Sound & sound, const Vector2f ballPos, const float radius) {
	FloatRect playerBounds = getMainPlayerBounds();
	FloatRect rangeBounds = redRange.getGlobalBounds();
	Vector2f pos1P = getMainPlayerPos();
	static Clock CDTime;
	static bool flashCD = false;

	if (!flashCD) {
		if (game::ballRectINCIntersects(ballPos, radius, playerBounds)) {
			elapsed.restart();
			sound.play();
			if (ballPos.x - radius <= playerBounds.left) {
				setFlashPosition(playerBounds.left + rangeBounds.width / 2, pos1P.y);
			}
			else if (ballPos.x + radius >= playerBounds.left + playerBounds.width) {
				setFlashPosition(playerBounds.left + playerBounds.width - rangeBounds.width / 2, pos1P.y);
			}
			else {
				setFlashPosition(ballPos.x, pos1P.y);
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
