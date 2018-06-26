#include "mainBall.h"
#include "block.h"
#include "brick.h"
#include "../../definition/gameState.h"
#include "../../definition/intersects.h"

using namespace item;
using namespace sf;

MainBall::MainBall()
	: settle(false) {
	setColor(Color::Green);
}

bool MainBall::isCollidedObstacle(const Block * block) {
	const float radius = getRadius();
	const Vector2f ballPos = getPosition();
	const Vector2f blockSpeed(block->getSpeed());
	const sys::DPointf boundDP(block->getDP());
	if (sys::ballRectINCIntersects(ballPos, radius, boundDP)) {
		restartClock();
		if (ballPos.x < boundDP.dot1.x) {
			left = true;
			setSpeedX(-std::max(abs(getSpeed().x), abs(blockSpeed.x)));
		}
		else if (ballPos.x > boundDP.dot2.x) {
			right = true;
			setSpeedX(std::max(abs(getSpeed().x), abs(blockSpeed.x)));
		}

		if (ballPos.y > boundDP.dot2.y) {
			bottom = true;
			setSpeedY(std::max(abs(getSpeed().y), abs(blockSpeed.y)));
		}
		else if (ballPos.y < boundDP.dot1.y) {
			top = true;
			setSpeedY(-std::max(abs(getSpeed().y), abs(blockSpeed.y)));
		}
		CD = false;
		return true;
	}
	return false;
}

bool MainBall::isCollidedWall(const Brick * brick) {
	const float radius = getRadius();
	const Vector2f ballPos = getPosition();
	const sys::DPointf boundDP(brick->getDP());
	if (sys::ballRectINCIntersects(ballPos, radius, boundDP)) {
		restartClock();
		if (ballPos.x < boundDP.dot1.x) {
			setSpeedX(-abs(getSpeed().x));
		}
		else if (ballPos.x > boundDP.dot2.x) {
			setSpeedX(abs(getSpeed().x));
		}

		if (ballPos.y > boundDP.dot2.y) {
			setSpeedY(abs(getSpeed().y));
		}
		else if (ballPos.y < boundDP.dot1.y) {
			setSpeedY(-abs(getSpeed().y));
		}
		CD = false;
		return true;
	}
	return false;
}

void MainBall::initialize() {
	setSpeedX((prng(150) % 150 * .01f + 1.5f) * (rng() < 0 ? 1 : -1));
	setSpeedY(-1.5f);
	setActive(false);
	settle = true;
}

void MainBall::resettle() {
	if (game::currentState != GameState::LEVEL_FINISHED) throw std::invalid_argument("Level not finished.");
	settle = false;
}

bool MainBall::isSettle() const {
	return settle;
}

MainBall::~MainBall() {
}

void MainBall::determineUpdate() {
	const Vector2f ballPos = getPosition();
	const float radius = getRadius();
	if (!broke) {
		if (left && right) {
			broke = true;
		}
		else if (left && ballPos.x - radius < 0.0f) {
			broke = true;
		}
		else if (right && ballPos.x + radius > LEVEL_WIDTH) {
			broke = true;
		}
		else if (top && bottom) {
			broke = true;
		}
		else if (top && ballPos.y + radius > LEVEL_HEIGHT) {
			broke = true;
		}
	}
	if (broke) {
		broke = false;
		settle = false;
		game::currentState = GameState::NOT_READY;
	}
	left = false;
	right = false;
	top = false;
	bottom = false;
}
