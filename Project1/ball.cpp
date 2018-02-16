#include "define.h"
#include "ball.h"
#include <algorithm>

using namespace std;
using namespace sf;
using namespace item;

Ball::Ball(const Player &player) {
	balls.resize(1);
	balls.at(0) = unique_ptr<BallContent>(new BallContent(player));
}

void Ball::initializeBall() {

	if (!balls.empty()) {
		balls.at(0)->ballSpeed.x = static_cast<float>((rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1));
		balls.at(0)->ballSpeed.y = 2.f;
	}
}

void Ball::ballEnableMove(Player &player, Sound & sound) {

	if (!balls.empty()) {
		if (GameState::start) {
			flashRange(player, sound);
		}

		if (flash) {
			flashElapsed(player);
		}
	}
}

void Ball::move(const Player & player) {

	FloatRect playerBounds = player.getMainPlayerBounds();
	Vector2f playerPos = player.getMainPlayerPosition();
	for (size_t i = 0; i < balls.size(); ++i) {
		balls.at(i)->ballMove(playerBounds, playerPos);
		balls.at(i)->update();
		if (balls.at(i)->broke) {
			balls.erase(balls.begin() + i);
		}
	}
}

void Ball::flashRange(Player &player, Sound & sound) {

	FloatRect playerBounds = player.getMainPlayerBounds();
	FloatRect ballBounds = balls.at(0)->ball.getGlobalBounds();
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
			player.setFlashPosition(balls.at(0)->ball.getPosition().x, player.getMainPlayerPosition().y);
		}
		flash = true;
	}
}

void Ball::followPlayer(const Player & player) {
	if (!balls.empty()) {
		balls.at(0)->ball.setPosition(player.getMainPlayerPosition().x, player.getMainPlayerBounds().top - balls.at(0)->ball.getGlobalBounds().height / 2);
	}
}

void Ball::ballCollided(const FloatRect & bounds, const Vector2f &speed) {

	FloatRect leftBounds(bounds.left, bounds.top, 2.f, bounds.height);
	FloatRect rightBounds(bounds.left + bounds.width - 2.f, bounds.top, 2.f, bounds.height);
	FloatRect TopBounds(bounds.left, bounds.top, bounds.width, 2.f);
	FloatRect BottomBounds(bounds.left, bounds.top + bounds.height - 2.f, bounds.width, 2.f);

	for (size_t i = 0; i < balls.size(); ++i) {

		if (balls.at(i)->ball.getGlobalBounds().intersects(leftBounds)) {
			balls.at(i)->left = true;
			balls.at(i)->ballSpeed.x = min(-abs(balls.at(i)->ballSpeed.x), -abs(speed.x));
		}
		else if (balls.at(i)->ball.getGlobalBounds().intersects(rightBounds)) {
			balls.at(i)->right = true;
			balls.at(i)->ballSpeed.x = max(abs(balls.at(i)->ballSpeed.x), abs(speed.x));

		}

		if (balls.at(i)->ball.getGlobalBounds().intersects(BottomBounds)) {
			balls.at(i)->bottom = true;
			balls.at(i)->ballSpeed.y = max(abs(balls.at(i)->ballSpeed.y), abs(speed.y));
		}
		else if (balls.at(i)->ball.getGlobalBounds().intersects(TopBounds)) {
			balls.at(i)->top = true;
			balls.at(i)->ballSpeed.y = min(-abs(balls.at(i)->ballSpeed.y), -abs(speed.y));
		}
	}
}

bool Ball::ballCollided(const FloatRect & bounds) {

	FloatRect leftBounds(bounds.left, bounds.top, 2.f, bounds.height);
	FloatRect rightBounds(bounds.left + bounds.width - 2.f, bounds.top, 2.f, bounds.height);
	FloatRect TopBounds(bounds.left, bounds.top, bounds.width, 2.f);
	FloatRect BottomBounds(bounds.left, bounds.top + bounds.height - 2.f, bounds.width, 2.f);

	for (size_t i = 0; i < balls.size(); ++i) {

		if (balls.at(i)->ball.getGlobalBounds().intersects(bounds)) {
			if (balls.at(i)->ball.getGlobalBounds().intersects(leftBounds)) {
				balls.at(i)->ballSpeed.x = -abs(balls.at(i)->ballSpeed.x);
			}
			else if (balls.at(i)->ball.getGlobalBounds().intersects(rightBounds)) {
				balls.at(i)->ballSpeed.x = abs(balls.at(i)->ballSpeed.x);
			}

			if (balls.at(i)->ball.getGlobalBounds().intersects(BottomBounds)) {
				balls.at(i)->ballSpeed.y = abs(balls.at(i)->ballSpeed.y);
			}
			else if (balls.at(i)->ball.getGlobalBounds().intersects(TopBounds)) {
				balls.at(i)->ballSpeed.y = -abs(balls.at(i)->ballSpeed.y);
			}
			return true;
		}
	}
	return false;
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
	for (size_t i = 0; i < balls.size(); ++i) {
		target.draw(balls.at(i)->ball, states);
	}
}

Ball::BallContent::BallContent(const Player &player) {

	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::Black);
	ball.setRadius(5.f);
	ball.setOrigin(Vector2f(ball.getRadius(), ball.getRadius()));
	ball.setOutlineThickness(2.f);
	ball.setPosition(player.getMainPlayerPosition().x, player.getMainPlayerBounds().top - ball.getLocalBounds().height / 2);
	setMainColor(Color::Green);
	main = true;
}

Ball::BallContent::BallContent() {
	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::Black);
	ball.setRadius(5.f);
	ball.setOrigin(Vector2f(ball.getRadius(), ball.getRadius()));
	ball.setOutlineThickness(2.f);
}

void Ball::BallContent::setMainColor(const Color &color) {

	ball.setFillColor(color);
}

void Ball::BallContent::ballMove(const FloatRect &bounds, const Vector2f &position) {

	FloatRect ballBounds = ball.getGlobalBounds();
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
	else if (ballBounds.intersects(bounds)) {

		countTime.restart();
		if (ballSpeed.x == 0.0f) {
			ballSpeed.x = originX;
		}

		ballSpeed.y = -abs(ballSpeed.y);
		if (ball.getPosition().y <= position.y) {

			// right side of player position
			if (ball.getPosition().x >= bounds.left + bounds.width) {
				ballSpeed.x = abs(ballSpeed.x) * 1.2f;
			}
			else if (ball.getPosition().x > bounds.left + bounds.width * .9f) {
				ballSpeed.x = abs(ballSpeed.x) * 1.15f;
			}
			else if (ball.getPosition().x > bounds.left + bounds.width * .75f) {
				ballSpeed.x = abs(ballSpeed.x) * 1.1f;
			}
			else if (ball.getPosition().x > bounds.left + bounds.width * .55f) {
				ballSpeed.x = abs(ballSpeed.x) * 1.05f;
			}
			// left side of player position
			else if (ball.getPosition().x <= bounds.left) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.2f;
			}
			else if (ball.getPosition().x < bounds.left + bounds.width * .1f) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.15f;
			}
			else if (ball.getPosition().x < bounds.left + bounds.width * .25f) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.1f;
			}
			else if (ball.getPosition().x < bounds.left + bounds.width * .45f) {
				ballSpeed.x = -abs(ballSpeed.x) * 1.05f;
			}
			// hit center range(0.45f ~ 0.55f) will reset all speed, ballSpeed.x will not change direct
			// center position
			else if (ball.getPosition().x == bounds.left + bounds.width / 2) {
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
				if (ball.getPosition().x > bounds.left + bounds.width / 2) {
					ballSpeed.x = BOOST;
				}
				else if (ball.getPosition().x < bounds.left + bounds.width / 2) {
					ballSpeed.x = -BOOST;
				}
			}
			// after first hit
			else {
				if (ball.getPosition().x > bounds.left + bounds.width / 2) {
					ballSpeed.x = abs(ballSpeed.x) * .6f * BOOST;
				}
				else if (ball.getPosition().x < bounds.left + bounds.width / 2) {
					ballSpeed.x = -abs(ballSpeed.x) * .6f * BOOST;
				}
			}
			ballSpeed.y = -abs(ballSpeed.y) * 1.1f;
		}

		// prevent speed too fast
		if (abs(ballSpeed.x) >= MAXSPEED) {
			if (ball.getPosition().x > position.x) {
				ballSpeed.x = MAXSPEED;
			}
			else if (ball.getPosition().x < position.x) {
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
	ball.move(ballSpeed.x, ballSpeed.y);
}

void Ball::BallContent::update() {

	FloatRect ballBounds = ball.getGlobalBounds();
	if (!broke) {
		if (left) {
			if (right) {
				broke = true;
			}
			else if (ballBounds.left < 0.0f) {
				broke = true;
			}
		}
		else if (right) {
			if (left) {
				broke = true;
			}
			else if (ballBounds.left + ballBounds.width > STAGE_WIDTH) {
				broke = true;
			}
		}
		if (top) {
			if (bottom) {
				broke = true;
			}
			else if (ballBounds.top + ballBounds.height > STAGE_HEIGHT) {
				broke = true;
			}
		}
		else if (bottom) {
			if (top) {
				broke = true;
			}
			else if (ballBounds.top < 0.0f) {
				broke = true;
			}
		}
	}
	if (main && broke) {
		broke = false;
		GameState::start = false;
		GameState::ready = false;
	}
	left = false;
	right = false;
	top = false;
	bottom = false;
}

void Ball::BallContent::resetBall() {

	ballSpeed.x = static_cast<float>((rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1));
	ballSpeed.y = 2.f * (rng() % 100 < 50 ? 1 : -1);
}
