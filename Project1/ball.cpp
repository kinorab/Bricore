#include "define.h"
#include "ball.h"

using namespace std;
using namespace sf;
using namespace item;

Vector2f Ball::ballSpeed;

Ball::Ball(const Player &player) {

	mainBall.setFillColor(Color::White);
	mainBall.setOutlineColor(Color::Black);
	mainBall.setRadius(5.f);
	mainBall.setOutlineThickness(2.f);
	mainBall.setOrigin(Vector2f(mainBall.getRadius(), mainBall.getRadius()));
	mainBall.setPosition(player.getMainPlayerPosition().x, player.getMainPlayerBounds().top - mainBall.getLocalBounds().height / 2);
}

void Ball::initializeBall() {

	ballSpeed.x = static_cast<float>((rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1));
	ballSpeed.y = 3.f;
}

void Ball::resetBall() {

	ballSpeed.x = static_cast<float>((rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1));
	ballSpeed.y = 3.f * (rng() % 100 < 50 ? 1 : -1);
}

void Ball::ballEnableMove(Player &player, Sound & sound) {

	if (GameState::start) {
		flashRange(player, sound);
	}

	if (flash) {
		flashElapsed(player);
	}
}

void Ball::ballMove(const Player & player) {

	FloatRect playerBounds = player.getMainPlayerBounds();
	FloatRect ballBounds = mainBall.getGlobalBounds();
	static float originX = ballSpeed.x;
	static float originY = ballSpeed.y;
	static Clock countTime;
	// when left mouse click will only set initial speed once
	if (GameState::active) {
		originX = ballSpeed.x;
		originY = ballSpeed.y;
		countTime.restart();
		GameState::active = false;
	}
	else if (countTime.getElapsedTime().asSeconds() > RESETTIME && GameState::start) {
		// preserve last speed then add 60% extra origin speed to new speed
		float tempX = ballSpeed.x;
		float tempY = ballSpeed.y;
		resetBall();
		originX = ballSpeed.x;
		originY = ballSpeed.y;
		ballSpeed.x >= 0 ? ballSpeed.x += (abs(tempX) - ballSpeed.x) * .6f
			: ballSpeed.x += -(abs(tempX) + ballSpeed.x) * .6f;
		ballSpeed.y >= 0 ? ballSpeed.y += (abs(tempY) - ballSpeed.y) * .6f
			: ballSpeed.y += -(abs(tempY) + ballSpeed.y) * .6f;
		countTime.restart();
	}

	// out of bottom bound, reset the mainBall
	if (ballBounds.top > STAGE_HEIGHT) {
		GameState::start = false;
		GameState::ready = false;
	}
	// window's right bound
	else if (ballBounds.left + ballBounds.width >= STAGE_WIDTH) {
		ballSpeed.x = -abs(ballSpeed.x);
	}
	// window's left bound
	else if (ballBounds.left <= 0) {
		ballSpeed.x = abs(ballSpeed.x);
	}
	// window's top bound
	else if (ballBounds.top <= 0) {
		ballSpeed.y = abs(ballSpeed.y);
	}
	// the collision between mainBall and player
	else if (ballBounds.intersects(playerBounds)) {

		countTime.restart();
		if (ballSpeed.x == 0.0f) {
			ballSpeed.x = originX;
		}

		ballSpeed.y = -abs(ballSpeed.y);
		if (mainBall.getPosition().y <= player.getMainPlayerPosition().y) {

			// right side of player position
			if (mainBall.getPosition().x >= playerBounds.left + playerBounds.width) {
				ballSpeed.x = abs(ballSpeed.x) * 1.2f;
			}
			else if (mainBall.getPosition().x > playerBounds.left + playerBounds.width * .9f) {
				ballSpeed.x = abs(ballSpeed.x) * 1.15f;
			}
			else if (mainBall.getPosition().x > playerBounds.left + playerBounds.width * .75f) {
				ballSpeed.x = abs(ballSpeed.x) * 1.1f;
			}
			else if (mainBall.getPosition().x > playerBounds.left + playerBounds.width * .55f) {
				ballSpeed.x = abs(ballSpeed.x) * 1.05f;
			}
			// left side of player position
			else if (mainBall.getPosition().x <= playerBounds.left) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.2f;
			}
			else if (mainBall.getPosition().x < playerBounds.left + playerBounds.width * .1f) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.15f;
			}
			else if (mainBall.getPosition().x < playerBounds.left + playerBounds.width * .25f) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.1f;
			}
			else if (mainBall.getPosition().x < playerBounds.left + playerBounds.width * .45f) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.05f;
			}
			// hit center range(0.45f ~ 0.55f) will reset all speed, ballSpeed.x will not change direct
			// center position
			else if (mainBall.getPosition().x == playerBounds.left + playerBounds.width / 2) {
				ballSpeed.x = 0.0f;
				ballSpeed.y = -abs(originY);
			}
			else {
				ballSpeed.x < 0 ? ballSpeed.x = -abs(originX) : ballSpeed.x = abs(originX);
				ballSpeed.y = -abs(originY);
			}
		}
		// the collision under the half of player body
		else {

			// first hit
			if (abs(ballSpeed.x) < BOOST) {
				if (mainBall.getPosition().x > playerBounds.left + playerBounds.width / 2) {
					ballSpeed.x = BOOST;
				}
				else if (mainBall.getPosition().x < playerBounds.left + playerBounds.width / 2) {
					ballSpeed.x = -BOOST;
				}
			}
			// after first hit
			else {
				if (mainBall.getPosition().x > playerBounds.left + playerBounds.width / 2) {
					ballSpeed.x = abs(ballSpeed.x) * .6f * BOOST;
				}
				else if (mainBall.getPosition().x < playerBounds.left + playerBounds.width / 2) {
					ballSpeed.x = -abs(ballSpeed.x) * .6f * BOOST;
				}
			}
			ballSpeed.y = -abs(ballSpeed.y) * 1.1f;
		}

		// prevent speed too fast
		if (abs(ballSpeed.x) >= MAXSPEED) {
			if (mainBall.getPosition().x > player.getMainPlayerPosition().x) {
				ballSpeed.x = MAXSPEED;
			}
			else if (mainBall.getPosition().x < player.getMainPlayerPosition().x) {
				ballSpeed.x = -MAXSPEED;
			}
			else {
				ballSpeed.x < 0 ? ballSpeed.x = MAXSPEED : ballSpeed.x = -MAXSPEED;
			}
		}
		else if (abs(ballSpeed.y) >= abs(originY) * 5) {
			ballSpeed.y = -abs(originY) * 5;
		}
	}
	mainBall.move(ballSpeed.x, ballSpeed.y);
}

void Ball::flashRange(Player &player, Sound & sound) {

	FloatRect playerBounds = player.getMainPlayerBounds();
	FloatRect ballBounds = mainBall.getGlobalBounds();
	FloatRect rangeBounds = player.getFlashBounds();

	if (ballBounds.intersects(playerBounds)) {
		elapsed.restart();
		sound.play();
		if (ballBounds.left <= playerBounds.left) {
			player.setFlashPosition(playerBounds.left + rangeBounds.width / 2, player.getMainPlayerPosition().y);
		}
		else if (ballBounds.left + ballBounds.width >= playerBounds.left + playerBounds.width) {
			player.setFlashPosition(playerBounds.left + playerBounds.width - rangeBounds.width / 2, player.getMainPlayerPosition().y);
		}
		else {
			player.setFlashPosition(mainBall.getPosition().x, player.getMainPlayerPosition().y);
		}
		flash = true;
	}
}

void Ball::followPlayer(const Player & player) {
	mainBall.setPosition(player.getMainPlayerPosition().x, player.getMainPlayerBounds().top - mainBall.getGlobalBounds().height / 2);
}

void Ball::setMainBallPosition(const Vector2f & position) {
	mainBall.setPosition(position);
}

void Ball::setMainBallPosition(const float posX, const float posY) {
	mainBall.setPosition(posX, posY);
}

const FloatRect & Ball::getMainBallBound() const {
	return mainBall.getGlobalBounds();
}

const float Ball::getMainBallRadius() const {
	return mainBall.getRadius();
}

const Vector2f & Ball::getMainBallPosition() const {
	return mainBall.getPosition();
}

void Ball::flashElapsed(Player & player) {

	float time = static_cast<float>(elapsed.getElapsedTime().asMilliseconds());
	if (time <= 1500.f) {
		float rate = (1.f - time / 1500.f);
		player.setFlashFillColor(Color(static_cast<Uint8>(255), static_cast<Uint8>(0), static_cast<Uint8>(0), static_cast<Uint8>(rate * 255)));
	}
	else {
		flash = false;
	}
}

void Ball::draw(RenderTarget &target, RenderStates states) const {

	states.texture = NULL;
	target.draw(mainBall, states);
}
