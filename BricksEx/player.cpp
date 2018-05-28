#include "player.h"
#include "define.h"
#include "audioManager.h"
#include "intersects.h"

using namespace sf;

Player::Player()
	: mainPlayer(RectangleShape(Vector2f(240, 12)))
	, yellowRange(RectangleShape(Vector2f(mainPlayer.getSize().x * 0.1f, mainPlayer.getSize().y)))
	, redRange(RectangleShape(Vector2f(mainPlayer.getSize().x * 0.05f, mainPlayer.getSize().y)))
	, flash(false)
	, flashCD(false) {

	mainPlayer.setOrigin(Vector2f(mainPlayer.getSize().x / 2, mainPlayer.getSize().y / 2));
	mainPlayer.setFillColor(Color::Green);
	mainPlayer.setPosition(Vector2f(LEVEL_WIDTH / 2, LEVEL_HEIGHT - mainPlayer.getSize().y));
	yellowRange.setOrigin(Vector2f(yellowRange.getSize().x / 2, yellowRange.getSize().y / 2));
	yellowRange.setPosition(mainPlayer.getPosition());
	yellowRange.setFillColor(Color::Yellow);
	redRange.setOrigin(Vector2f(redRange.getSize().x / 2, redRange.getSize().y / 2));
	redRange.setPosition(mainPlayer.getPosition());
	redRange.setFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(0)));
	GameState::playerArea.setSize(Vector2f(LEVEL_WIDTH, 100.f));
	GameState::playerArea.setPosition(0.0f, LEVEL_HEIGHT - 100.f);
}

Player::Player(const Player & copy)
	: flash(copy.flash)
	, flashCD(copy.flash)
	, CDTime(copy.CDTime)
	, elapsed(copy.elapsed)
	, mainPlayer(copy.mainPlayer)
	, redRange(copy.redRange)
	, yellowRange(copy.yellowRange) {

}

void Player::update(const Vector2f &ballPos, const float ballRadius) {
	const FloatRect playerBound = mainPlayer.getGlobalBounds();
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
		flashRange(AudioManager::getInstance()->sound1, ballPos, ballRadius);
	}
	if (flash) {
		flashElapsed();
	}

	yellowRange.setPosition(mainPlayer.getPosition());
}

void Player::preUpdate(const sf::Vector2f & ballPos, const float ballRadius, const float intervalTime) {
	const FloatRect playerBound = mainPlayer.getGlobalBounds();
	if (playerBound.left >= 0
		&& (Keyboard::isKeyPressed(Keyboard::Left))
		) {
		mainPlayer.move(Vector2f((-MAINPLAYERSPEED / SLICE) * intervalTime, 0));
		redRange.move(Vector2f((-MAINPLAYERSPEED / SLICE) * intervalTime, 0));
	}
	if (playerBound.left + playerBound.width <= LEVEL_WIDTH
		&& (Keyboard::isKeyPressed(Keyboard::Right))
		) {
		mainPlayer.move(Vector2f((MAINPLAYERSPEED / SLICE) * intervalTime, 0));
		redRange.move(Vector2f((MAINPLAYERSPEED / SLICE) * intervalTime, 0));
	}
	if (GameState::start) {
		flashRange(AudioManager::getInstance()->sound1, ballPos, ballRadius);
	}
	if (flash) {
		flashElapsed();
	}

	yellowRange.setPosition(mainPlayer.getPosition());
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

const sys::DPointf Player::getMainPlayerDP() const {
	return sys::DPointf(mainPlayer.getGlobalBounds());
}

Player::~Player(){ }

Player & Player::operator=(const Player &right) {
	flash = right.flash;
	flashCD = right.flashCD;
	CDTime = right.CDTime;
	elapsed = right.elapsed;
	mainPlayer = right.mainPlayer;
	redRange = right.redRange;
	yellowRange = right.yellowRange;
	return *this;
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
	const FloatRect playerBounds = getMainPlayerBounds();
	const FloatRect rangeBounds = redRange.getGlobalBounds();
	const Vector2f pos1P = getMainPlayerPos();

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
