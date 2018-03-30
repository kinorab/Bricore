#include "player.h"
#include "define.h"
#include <iostream>

using namespace sf;

bool Player::flash = false;

Player::Player(const float playerSpeed) {
	mainPlayerSpeed = playerSpeed;
	mainPlayer.setSize(Vector2f(240, 12));
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(LEVEL_WIDTH / 2, LEVEL_HEIGHT - mainPlayer.getSize().y));
	yellowRange.setSize(Vector2f(mainPlayer.getSize().x * 0.1f, mainPlayer.getSize().y));
	yellowRange.setOrigin(Vector2f(yellowRange.getSize().x / 2, yellowRange.getSize().y / 2));
	yellowRange.setPosition(mainPlayer.getPosition());
	yellowRange.setFillColor(Color::Yellow);
	redRange.setSize(Vector2f(yellowRange.getSize().x / 2, mainPlayer.getSize().y));
	redRange.setOrigin(Vector2f(redRange.getSize().x / 2, redRange.getSize().y / 2));
	redRange.setPosition(mainPlayer.getPosition());
	redRange.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0)));
}

void Player::playerMove(Sound &sound, const FloatRect &ballBounds, const Vector2f &mainBallPos) {
	FloatRect playerBound = mainPlayer.getGlobalBounds();
	if (playerBound.left > 0.0
		&& (Keyboard::isKeyPressed(Keyboard::Left))
		) {
		mainPlayer.move(Vector2f(-abs(mainPlayerSpeed), 0.0));
		redRange.move(Vector2f(-abs(mainPlayerSpeed), 0.0));
	}
	if (playerBound.left + playerBound.width < LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(Keyboard::Right))
		) {
		mainPlayer.move(Vector2f(abs(mainPlayerSpeed), 0.0));
		redRange.move(Vector2f(abs(mainPlayerSpeed), 0.0));
	}
	if (GameState::start) {
		flashRange(sound, ballBounds, mainBallPos);
	}
	if (flash) {
		flashElapsed();
	}

	yellowRange.setPosition(mainPlayer.getPosition());
}

void Player::setMainPlayerSpeed(const float playerSpeed) {
	try {
		if (playerSpeed >= 0.0) {
			mainPlayerSpeed = playerSpeed;
		}
		else {
			std::invalid_argument("Player's speed can't be negative.");
		}
	}
	catch (std::invalid_argument &ex) {
		std::cout << "Invalid_argument: " << ex.what() << std::endl;
	}
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

const float Player::getMainPlayerSpeed() const {
	return mainPlayerSpeed;
}

const Vector2f & Player::getMainPlayerPos() const {
	return mainPlayer.getPosition();
}

const Vector2f Player::getMainPlayerTopCenterPos() const {
	return Vector2f(mainPlayer.getPosition().x, mainPlayer.getGlobalBounds().top);
}

const FloatRect Player::getMainPlayerBounds() const {
	return mainPlayer.getGlobalBounds();
}

const FloatRect Player::getFlashBounds() const {
	return redRange.getGlobalBounds();
}

void Player::draw(RenderTarget &target, RenderStates states) const {
	states.texture = nullptr;
	target.draw(mainPlayer, states);
	target.draw(yellowRange, states);
	target.draw(redRange, states);
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

void Player::flashRange(Sound & sound, const FloatRect &ballBounds, const Vector2f &ballPos) {
	FloatRect playerBounds = getMainPlayerBounds();
	FloatRect rangeBounds = getFlashBounds();
	Vector2f pos1P = getMainPlayerPos();

	if (ballBounds.intersects(playerBounds)) {
		elapsed.restart();
		sound.play();
		if (ballBounds.left <= playerBounds.left) {
			setFlashPosition(playerBounds.left + rangeBounds.width / 2, pos1P.y);
		}
		else if (ballBounds.left + ballBounds.width >= playerBounds.left + playerBounds.width) {
			setFlashPosition(playerBounds.left + playerBounds.width - rangeBounds.width / 2, pos1P.y);
		}
		else {
			setFlashPosition(ballPos.x, pos1P.y);
		}
		flash = true;
	}
}
