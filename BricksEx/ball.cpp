#include "ball.h"
#include "brick.h"
#include "player.h"
#include "obstacle.h"
#include "define.h"
#include "intersects.h"
#include <algorithm>
#include <iostream>

using namespace sf;
using namespace item;

bool Ball::mainSettled(false);
bool Ball::initialize(false);
std::shared_ptr<Ball> Ball::instance = nullptr;

Ball::Ball() :
	multiple(false)
	, ballStartC(false) {
	balls.push_back(std::shared_ptr<BallContainer>(new BallContainer()));
}

std::shared_ptr<Ball> Ball::getInstance() {
	if (!instance) {
		instance = std::shared_ptr<Ball>(new Ball());
		instance->followPlayer();
	}
	return instance;
}

std::shared_ptr<Ball> item::Ball::getPredictInstance() {
	static std::shared_ptr<Ball> preInstance;
	static Ball predict;
	if (instance) {
		predict = *instance;
		predict.update();
		preInstance = std::make_shared<Ball>(predict);
		return preInstance;
	}
	return nullptr;
}

const bool Ball::resetInstance() {
	if (instance) {
		instance.reset();
		return true;
	}
	return false;
}

void Ball::update() {
	for (size_t i = 0; i < balls.size(); ++i) {
		balls.at(i)->move(Player::getInstance()->getMainPlayerDP());
		if (balls.at(i)->broke) {
			balls.erase(balls.begin() + i);
		}
		if (multiple) {
			collision(i);
		}
	}
}

void Ball::initializeBall() {
	if (!initialize && !balls.empty()) {
		balls.erase(balls.begin() + 1, balls.end());
		balls.at(0)->setSpeedX((prng(200) % 200 * .01f + 2.f) * (rng() < 0 ? 1 : -1));
		balls.at(0)->setSpeedY(-2.f);
		balls.at(0)->active = false;
		initialize = true;
	}
	else if (GameState::finishLevel) {
		initialize = false;
		GameState::finishLevel = false;
	}
}

void Ball::followPlayer() {
	if (!balls.empty()) {
		Vector2f pos = Player::getInstance()->getMainPlayerTopCenterPos();
		balls.at(0)->setPos(pos.x, pos.y - balls.at(0)->getRad() - 1.f);
	}
}

void Ball::ballCollided(const size_t number, const size_t blockNumber) {
	const float radius = balls.at(number)->getRad();
	const Vector2f ballPos = balls.at(number)->getPos();
	const sys::DPointf boundsDP = Obstacle::getInstance()->getDP(blockNumber);
	const Vector2f speed = Obstacle::getInstance()->getBlockSpeed(blockNumber);
	if (game::ballRectINCIntersects(ballPos, radius, boundsDP)) {
		if (ballPos.x < boundsDP.dot1.x) {
			balls.at(number)->left = true;
			balls.at(number)->setSpeedX(-std::max(abs(balls.at(number)->getSpeedX()), abs(speed.x)));
		}
		else if (ballPos.x > boundsDP.dot2.x) {
			balls.at(number)->right = true;
			balls.at(number)->setSpeedX(std::max(abs(balls.at(number)->getSpeedX()), abs(speed.x)));

		}

		if (ballPos.y > boundsDP.dot2.y) {
			balls.at(number)->bottom = true;
			balls.at(number)->setSpeedY(std::max(abs(balls.at(number)->getSpeedY()), abs(speed.y)));
		}
		else if (ballPos.y < boundsDP.dot1.y) {
			balls.at(number)->top = true;
			balls.at(number)->setSpeedY(-std::max(abs(balls.at(number)->getSpeedY()), abs(speed.y)));
		}
		balls.at(number)->CD = false;
	}
}

const bool Ball::isBallCollided(const size_t number, const size_t brickNumber) {
	const float radius = balls.at(number)->getRad();
	const Vector2f ballPos = balls.at(number)->getPos();
	const sys::DPointf boundsDP(Brick::getInstance()->getDP(brickNumber));
	if (game::ballRectINCIntersects(ballPos, radius, boundsDP)) {
		if (ballPos.x < boundsDP.dot1.x) {
			balls.at(number)->setSpeedX(-abs(balls.at(number)->getSpeedX()));
		}
		else if (ballPos.x > boundsDP.dot2.x) {
			balls.at(number)->setSpeedX(abs(balls.at(number)->getSpeedX()));
		}

		if (ballPos.y > boundsDP.dot2.y) {
			balls.at(number)->setSpeedY(abs(balls.at(number)->getSpeedY()));
		}
		else if (ballPos.y < boundsDP.dot1.y) {
			balls.at(number)->setSpeedY(-abs(balls.at(number)->getSpeedY()));
		}
		if (balls.at(number)->isMain()) {
			ballDivided(10);
		}
		balls.at(number)->CD = false;
		return true;
	}
	return false;
}

const bool Ball::isBallEnteredBlocksArea(const size_t number) const {
	const float radius = balls.at(number)->getRad();
	const Vector2f ballPos = balls.at(number)->getPos();
	return game::ballRectINCIntersects(ballPos, radius, Obstacle::getInstance()->getBlocksAreaDP());
}

const bool Ball::isBallEnteredBricksArea(const size_t number) const {
	const float radius = balls.at(number)->getRad();
	const Vector2f ballPos = balls.at(number)->getPos();
	return game::ballRectINCIntersects(ballPos, radius, Brick::getInstance()->getBrickAreaDP());
}

void Ball::ballDivided(const size_t numbers) {

	try {
		const Vector2f mainPos(balls.at(0)->getPos());
		const Vector2f mainSpeed(balls.at(0)->getSpeedX(), balls.at(0)->getSpeedY());
		for (size_t i = 0; i < numbers; ++i) {
			balls.push_back(std::shared_ptr<BallContainer>(new BallContainer()));
			balls.at(balls.size() - 1)->setPos(mainPos);
			balls.at(balls.size() - 1)->setSpeedX(mainSpeed.x * ((prng(50) % 50 + 50) * .01f * (rng() < 0 ? -1 : 1)));
			balls.at(balls.size() - 1)->setSpeedY(mainSpeed.y * ((prng(20) % 20 + 80) * .01f * (rng() < 0 ? -1 : 1)));
		}
		ballStartC = false;
		multiple = true;
	}
	catch (std::out_of_range &ex) {
		std::cout << "Cannot modify balls' amount: " << ex.what() << std::endl;
	}
}

const float Ball::getMainBallRadius() const {
	return balls.at(0)->getRad();
}

const Vector2f & Ball::getMainBallPosition() const {
	return balls.at(0)->getPos();
}

const size_t Ball::getBallsAmount() const {
	return balls.size();
}

Ball & item::Ball::operator =(const Ball &) = default;

void Ball::draw(RenderTarget &target, RenderStates states) const {
	states.texture = nullptr;
	for (size_t i = 0; i < balls.size(); ++i) {
		balls.at(i)->draw(target, states);
	}
}

void Ball::collision(const size_t number) {
	try {
		for (size_t j = number + 1; j < balls.size(); ++j) {
			const Vector2f APos = balls.at(number)->getPos();
			const float AR = balls.at(number)->getRad();
			const Vector2f BPos = balls.at(j)->getPos();
			const float BR = balls.at(j)->getRad();
			if (ballStartC && game::ballsIntersects(APos, AR, BPos, BR)) {
				const float avarageSpeedX = (abs(balls.at(number)->getSpeedX()) + abs(balls.at(j)->getSpeedX())) / 2;
				const float ASpeedY = balls.at(number)->getSpeedY();
				const float BSpeedY = balls.at(j)->getSpeedY();
				if (APos.x > BPos.x) {
					if (APos.y > BPos.y) {
						balls.at(number)->setSpeed(Vector2f(abs(avarageSpeedX), abs(ASpeedY)));
						balls.at(j)->setSpeed(Vector2f(-abs(avarageSpeedX), -abs(BSpeedY)));
					}
					else {
						balls.at(number)->setSpeed(Vector2f(abs(avarageSpeedX), -abs(ASpeedY)));
						balls.at(j)->setSpeed(Vector2f(-abs(avarageSpeedX), abs(BSpeedY)));
					}
				}
				else {
					if (APos.y > BPos.y) {
						balls.at(number)->setSpeed(Vector2f(-abs(avarageSpeedX), abs(ASpeedY)));
						balls.at(j)->setSpeed(Vector2f(abs(avarageSpeedX), -abs(BSpeedY)));
					}
					else {
						balls.at(number)->setSpeed(Vector2f(-abs(avarageSpeedX), -abs(ASpeedY)));
						balls.at(j)->setSpeed(Vector2f(abs(avarageSpeedX), abs(BSpeedY)));
					}
				}
			}
			else if (game::ballsDistance(APos, AR, BPos, BR) < 2.f) {
				return;
			}
		}
		if (!ballStartC) {
			ballStartC = true;
		}
	}
	catch (std::out_of_range &ex) {
		std::cout << "Exception: " << ex.what() << std::endl;
	}
}

Ball::BallContainer::BallContainer()
	: left(false)
	, right(false)
	, bottom(false)
	, top(false)
	, broke(false)
	, CD(false)
	, active(false)
	, main(false) {
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

void Ball::BallContainer::determineUpdate() {

	const Vector2f ballPos = getPos();
	const float radius = getRad();
	if (!broke) {
		if (left) {
			if (right) {
				broke = true;
			}
			else if (ballPos.x - radius < 0.0f) {
				broke = true;
			}
		}
		else if (right) {
			if (left) {
				broke = true;
			}
			else if (ballPos.x + radius > LEVEL_WIDTH) {
				broke = true;
			}
		}
		if (top) {
			if (bottom) {
				broke = true;
			}
			else if (ballPos.y + radius > LEVEL_HEIGHT) {
				broke = true;
			}
		}
		else if (bottom) {
			if (top) {
				broke = true;
			}
			else if (ballPos.y - radius < 0.0f) {
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

void Ball::BallContainer::move(const sys::DPointf &DP) {

	const Vector2f ballPos = getPos();
	const float radius = getRad();
	const Vector2f LT(DP.dot1);
	const Vector2f RB(DP.dot2);
	const float width = RB.x - LT.x;
	if (!active) {
		oriSpeed.x = ballSpeed.x;
		oriSpeed.y = ballSpeed.y;
		active = true;
		countTime.restart();
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
	if (ballPos.y - radius > LEVEL_HEIGHT) {
		broke = true;
	}
	// window's right bound
	else if (ballPos.x + radius >= LEVEL_WIDTH) {
		ballSpeed.x = -abs(ballSpeed.x);
	}
	// window's left bound
	else if (ballPos.x - radius <= 0) {
		ballSpeed.x = abs(ballSpeed.x);
	}
	// window's top bound
	else if (ballPos.y - radius <= 0) {
		ballSpeed.y = abs(ballSpeed.y);
	}
	// the collision between mainBall and player
	else if (game::ballRectINCIntersects(ballPos, radius, DP)) {
		if (!CD) {
			countTime.restart();
			if (ballSpeed.x == 0.0f) {
				ballSpeed.x = oriSpeed.x;
			}
			ballSpeed.y = -abs(ballSpeed.y);
			// hit between the player board
			if (ballPos.x <= RB.x && ballPos.x >= LT.x) {
				// right side of player position
				if (ballPos.x > LT.x + width * .9f) {
					ballSpeed.x = abs(ballSpeed.x) * 1.125f;
				}
				else if (ballPos.x > LT.x + width * .75f) {
					ballSpeed.x = abs(ballSpeed.x) * 1.075f;
				}
				else if (ballPos.x > LT.x + width * .55f) {
					ballSpeed.x = abs(ballSpeed.x) * 1.05f;
				}
				// left side of player position
				else if (ballPos.x < LT.x + width * .1f) {
					ballSpeed.x = -abs(ballSpeed.x) * 1.125f;
				}
				else if (ballPos.x < LT.x + width * .25f) {
					ballSpeed.x = -abs(ballSpeed.x) * 1.075f;
				}
				else if (ballPos.x < LT.x + width * .45f) {
					ballSpeed.x = -abs(ballSpeed.x) * 1.05f;
				}
				// hit center range(0.45f ~ 0.55f) will reset all speed, ballSpeed.x will not change direct
				// hit at center position
				else if (ballPos.x == LT.x + width / 2) {
					ballSpeed.x = 0.0f;
					ballSpeed.y = -abs(oriSpeed.y);
				}
				else {
					ballSpeed.x < 0 ? ballSpeed.x = -abs(oriSpeed.x) : ballSpeed.x = abs(oriSpeed.x);
					ballSpeed.y = -abs(oriSpeed.y);
				}
			}
			// hit at the player edge
			else {
				if (abs(ballSpeed.x) < MAINPLAYERSPEED) {
					if (ballPos.x > LT.x + width / 2) {
						ballSpeed.x = MAINPLAYERSPEED;
					}
					else if (ballPos.x < LT.x + width / 2) {
						ballSpeed.x = -MAINPLAYERSPEED;
					}
				}
				else {
					if (ballPos.x > LT.x + width / 2) {
						ballSpeed.x = abs(ballSpeed.x) * .6f * BOOST;
					}
					else if (ballPos.x < LT.x + width / 2) {
						ballSpeed.x = -abs(ballSpeed.x) * .6f * BOOST;
					}
				}
				ballSpeed.y = -abs(ballSpeed.y) * 1.1f;
			}
			CD = true;
			CDTime.restart();
		}
		else if (CDTime.getElapsedTime().asSeconds() > 0.1f) {
			CD = false;
		}
		// prevent speed too fast
		if (abs(ballSpeed.x) >= MAXSPEED) {
			if (ballSpeed.x < 0) {
				ballSpeed.x = -MAXSPEED;
			}
			else {
				ballSpeed.x = MAXSPEED;
			}
		}
	}
	ball.move(ballSpeed.x / SLICE, ballSpeed.y / SLICE);
	determineUpdate();
}

void Ball::BallContainer::setSpeedX(const float speedX) {
	ballSpeed.x = speedX;
}

void Ball::BallContainer::setSpeedY(const float speedY) {
	ballSpeed.y = speedY;
}

void Ball::BallContainer::setSpeed(const Vector2f &speed) {
	ballSpeed = speed;
}

void Ball::BallContainer::setPos(const Vector2f &pos) {
	ball.setPosition(pos.x, pos.y);
}

void Ball::BallContainer::setPos(const float posX, const float posY) {
	ball.setPosition(posX, posY);
}

void Ball::BallContainer::setRadius(const float radius) {
	ball.setRadius(radius);
}

void Ball::BallContainer::draw(RenderTarget &target, RenderStates states) const {
	target.draw(ball, states);
}

const bool Ball::BallContainer::isMain() const {
	return main;
}

const float Ball::BallContainer::getSpeedX() const {
	return ballSpeed.x;
}

const float Ball::BallContainer::getSpeedY() const {
	return ballSpeed.y;
}

const float Ball::BallContainer::getRad() const {
	return ball.getRadius() + ball.getOutlineThickness();
}

const Vector2f & Ball::BallContainer::getPos() const {
	return ball.getPosition();
}

void Ball::BallContainer::resetBall() {

	ballSpeed.x = (prng(200) % 200 * .01f + 2.f) * (rng() < 0 ? 1 : -1);
	ballSpeed.y = 2.f * (rng() < 0 ? 1 : -1);
}
