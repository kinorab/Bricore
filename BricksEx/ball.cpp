#include "define.h"
#include "ball.h"
#include <algorithm>
#include <iostream>

using namespace sf;
using namespace item;

bool Ball::initialize = false;
bool Ball::mainSettled = false;

Ball::Ball() {
	balls.push_back(std::unique_ptr<BallContainer>(new BallContainer()));
}

void Ball::initializeBall(const FloatRect &playerBounds, const Vector2f &playerPos) {
	if (!initialize && !balls.empty()) {
		balls.at(0)->ballSpeed.x = static_cast<float>((rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1));
		balls.at(0)->ballSpeed.y = -2.f;
		balls.erase(balls.begin() + 1, balls.end());
		initialize = true;
	}
	else if (GameState::finishLevel) {
		initialize = false;
		GameState::finishLevel = false;
	}
}

void Ball::update(const FloatRect &playerBounds, const Vector2f &playerPos) {

	for (size_t i = 0; i < balls.size(); ++i) {
		balls.at(i)->ballMove(playerBounds, playerPos);
		balls.at(i)->update();
		if (balls.at(i)->broke) {
			balls.erase(balls.begin() + i);
		}
	}
}

void Ball::followPlayer(const sf::Vector2f &playerTopCenterPos) {
	if (!balls.empty()) {
		balls.at(0)->ball.setPosition(playerTopCenterPos.x, playerTopCenterPos.y - balls.at(0)->ball.getGlobalBounds().height / 2);
	}
}

void Ball::ballCollided(const FloatRect & bounds, const Vector2f &speed) {

	FloatRect leftBounds(bounds.left, bounds.top, 2.f, bounds.height);
	FloatRect rightBounds(bounds.left + bounds.width - 2.f, bounds.top, 2.f, bounds.height);
	FloatRect TopBounds(bounds.left, bounds.top, bounds.width, 2.f);
	FloatRect BottomBounds(bounds.left, bounds.top + bounds.height - 2.f, bounds.width, 2.f);

	for (size_t i = 0; i < balls.size(); ++i) {

		if (balls.at(i)->ball.getGlobalBounds().intersects(bounds)) {
			if (balls.at(i)->ball.getGlobalBounds().intersects(leftBounds)) {
				balls.at(i)->left = true;
				balls.at(i)->ballSpeed.x = std::min(-abs(balls.at(i)->ballSpeed.x), -abs(speed.x));
			}
			else if (balls.at(i)->ball.getGlobalBounds().intersects(rightBounds)) {
				balls.at(i)->right = true;
				balls.at(i)->ballSpeed.x = std::max(abs(balls.at(i)->ballSpeed.x), abs(speed.x));

			}

			if (balls.at(i)->ball.getGlobalBounds().intersects(BottomBounds)) {
				balls.at(i)->bottom = true;
				balls.at(i)->ballSpeed.y = std::max(abs(balls.at(i)->ballSpeed.y), abs(speed.y));
			}
			else if (balls.at(i)->ball.getGlobalBounds().intersects(TopBounds)) {
				balls.at(i)->top = true;
				balls.at(i)->ballSpeed.y = std::min(-abs(balls.at(i)->ballSpeed.y), -abs(speed.y));
			}
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
			if (balls.at(i)->isMain()) {
				ballDivided(10);
			}
			return true;
		}
	}
	return false;
}

void Ball::ballDivided(const size_t numbers) {

	try {
		for (size_t i = 0; i < numbers; ++i) {
			balls.push_back(std::unique_ptr<BallContainer>(new BallContainer()));
			balls.at(balls.size() - 1)->ball.setPosition(balls.at(0)->ball.getPosition());
			balls.at(balls.size() - 1)->ballSpeed.x = balls.at(0)->ballSpeed.x * static_cast<float>((rng() % 50 + 50) * .01f * (rng() % 2 == 0 ? -1 : 1));
			balls.at(balls.size() - 1)->ballSpeed.y = balls.at(0)->ballSpeed.y * static_cast<float>((rng() % 25 + 75) * .01f * (rng() % 4 == 0 ? -1 : 1));
		}
	}
	catch (std::out_of_range &ex) {
		std::cout << "Cannot modify balls' amount: "<< ex.what() << std::endl;
	}
}

const FloatRect Ball::getMainBallBounds() const {
	return balls.at(0)->ball.getGlobalBounds();
}

const Vector2f & Ball::getMainBallPosition() const {
	return balls.at(0)->ball.getPosition();
}

void Ball::draw(RenderTarget &target, RenderStates states) const {

	states.texture = nullptr;
	for (size_t i = 0; i < balls.size(); ++i) {
		target.draw(balls.at(i)->ball, states);
	}
}


Ball::BallContainer::BallContainer() {
	ball.setFillColor(Color::White);
	ball.setOutlineColor(Color::Black);
	ball.setRadius(5.f);
	ball.setOrigin(Vector2f(ball.getRadius(), ball.getRadius()));
	ball.setOutlineThickness(2.f);
	if (!mainSettled) {
		setColor(Color::Green);
		main = true;
		mainSettled = true;
	}
}

void Ball::BallContainer::setColor(const Color &color) {

	ball.setFillColor(color);
}

void Ball::BallContainer::ballMove(const FloatRect &bounds, const Vector2f &position) {

	FloatRect ballBounds = ball.getGlobalBounds();
	if (active) {
		oriSpeed.x = ballSpeed.x;
		oriSpeed.y = ballSpeed.y;
		countTime.restart();
		active = false;
	}
	else if (countTime.getElapsedTime().asSeconds() > RESETTIME) {
		// preserve last speed then add 60% extra origin speed to new speed
		float tempX = ballSpeed.x;
		float tempY = ballSpeed.y;
		resetBall();
		oriSpeed.x = ballSpeed.x;
		oriSpeed.y = ballSpeed.y;
		ballSpeed.x >= 0 ? ballSpeed.x += (abs(tempX) - ballSpeed.x) * .6f
			: ballSpeed.x += -(abs(tempX) + ballSpeed.x) * .6f;
		ballSpeed.y >= 0 ? ballSpeed.y += (abs(tempY) - ballSpeed.y) * .6f
			: ballSpeed.y += -(abs(tempY) + ballSpeed.y) * .6f;
		countTime.restart();
	}

	// out of bottom bound, reset the mainBall
	if (ballBounds.top > LEVEL_HEIGHT) {
		broke = true;
	}
	// window's right bound
	else if (ballBounds.left + ballBounds.width >= LEVEL_WIDTH) {
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
			ballSpeed.x = oriSpeed.x;
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
				ballSpeed.y = -abs(oriSpeed.y);
			}
			else {
				ballSpeed.x < 0 ? ballSpeed.x = -abs(oriSpeed.x) : ballSpeed.x = abs(oriSpeed.x);
				ballSpeed.y = -abs(oriSpeed.y);
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
		else if (abs(ballSpeed.y) >= abs(oriSpeed.y) * 5) {
			ballSpeed.y = -abs(oriSpeed.y) * 5;
		}
	}
	ball.move(ballSpeed.x, ballSpeed.y);
}

void Ball::BallContainer::update() {

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
			else if (ballBounds.left + ballBounds.width > LEVEL_WIDTH) {
				broke = true;
			}
		}
		if (top) {
			if (bottom) {
				broke = true;
			}
			else if (ballBounds.top + ballBounds.height > LEVEL_HEIGHT) {
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
		initialize = false;
		GameState::start = false;
		GameState::ready = false;
	}
	left = false;
	right = false;
	top = false;
	bottom = false;
}

const bool Ball::BallContainer::isMain() const {
	return main;
}

void Ball::BallContainer::resetBall() {

	ballSpeed.x = static_cast<float>((rng() % 3 + 3) * (rng() % 2 == 0 ? 1 : -1));
	ballSpeed.y = 2.f * (rng() % 100 < 50 ? 1 : -1);
}
