#include "player.h"
#include "define.h"
#include <iostream>

using namespace sf;

Player::Player(const float playerSpeed) {

	mainPlayerSpeed = playerSpeed;
	mainPlayer.setSize(Vector2f(240, 12));
	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(STAGE_WIDTH / 2, STAGE_HEIGHT - mainPlayer.getSize().y));
	yellowRange.setSize(Vector2f(mainPlayer.getSize().x * 0.1f, mainPlayer.getSize().y));
	yellowRange.setOrigin(Vector2f(yellowRange.getSize().x / 2, yellowRange.getSize().y / 2));
	yellowRange.setFillColor(Color::Yellow);
	redRange.setSize(Vector2f(yellowRange.getSize().x / 2, mainPlayer.getSize().y));
	redRange.setOrigin(Vector2f(redRange.getSize().x / 2, redRange.getSize().y / 2));
	redRange.setPosition(mainPlayer.getPosition());
	redRange.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0)));
}

void Player::playerMove() {

	FloatRect playerBound = mainPlayer.getGlobalBounds();
	if (playerBound.left > 0
		&& (Keyboard::isKeyPressed(Keyboard::Left))
		) {
		mainPlayer.move(Vector2f(-abs(mainPlayerSpeed), 0));
		redRange.move(Vector2f(-abs(mainPlayerSpeed), 0));
	}

	if (playerBound.left + playerBound.width < STAGE_WIDTH
		&& (Keyboard::isKeyPressed(Keyboard::Right))
		) {
		mainPlayer.move(Vector2f(abs(mainPlayerSpeed), 0));
		redRange.move(Vector2f(abs(mainPlayerSpeed), 0));
	}

	yellowRange.setPosition(mainPlayer.getPosition());
}

void Player::setMainPlayerSpeed(const float playerSpeed) {

	if (playerSpeed >= 0) {
		mainPlayerSpeed = playerSpeed;
	}
	else {
		std::cout << "Player's speed can't be negative." << std::endl;
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

const sf::Vector2f & Player::getMainPlayerPosition() const {

	return mainPlayer.getPosition();
}

const sf::FloatRect Player::getMainPlayerBounds() const {

	return mainPlayer.getGlobalBounds();
}

const sf::FloatRect Player::getFlashBounds() const {

	return redRange.getGlobalBounds();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	states.texture = NULL;
	target.draw(mainPlayer, states);
	target.draw(yellowRange, states);
	target.draw(redRange, states);
}
