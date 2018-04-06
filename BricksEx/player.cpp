#include "player.h"
#include "define.h"
#include <iostream>

using namespace sf;

bool Player::flash = false;
sf::Clock Player::elapsed;
sf::RectangleShape Player::mainPlayer(Vector2f(240, 12));
sf::RectangleShape Player::yellowRange(Vector2f(mainPlayer.getSize().x * 0.1f, mainPlayer.getSize().y));
sf::RectangleShape Player::redRange(Vector2f(yellowRange.getSize().x / 2, mainPlayer.getSize().y));

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
}

void Player::playerMove(Sound &sound, const FloatRect &ballBounds) {
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
		flashRange(sound, ballBounds);
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

void Player::flashRange(Sound & sound, const FloatRect &ballBounds) {
	FloatRect playerBounds = getMainPlayerBounds();
	FloatRect rangeBounds = redRange.getGlobalBounds();
	Vector2f pos1P = getMainPlayerPos();
	static Clock CDTime;
	static bool flashCD = false;

	if (!flashCD) {
		if (game::INCIntersects(ballBounds, playerBounds)) {
			elapsed.restart();
			sound.play();
			if (ballBounds.left <= playerBounds.left) {
				setFlashPosition(playerBounds.left + rangeBounds.width / 2, pos1P.y);
			}
			else if (ballBounds.left + ballBounds.width >= playerBounds.left + playerBounds.width) {
				setFlashPosition(playerBounds.left + playerBounds.width - rangeBounds.width / 2, pos1P.y);
			}
			else {
				setFlashPosition(ballBounds.left + ballBounds.width, pos1P.y);
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
