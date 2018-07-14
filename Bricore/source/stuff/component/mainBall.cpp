#include "mainBall.h"
#include "block.h"
#include "brick.h"
#include "../../definition/gameState.h"
#include "../../definition/intersects.h"
#include <SFML/Graphics.hpp>

using namespace item;
using namespace sf;

MainBall::MainBall() noexcept
	: bSettle(false) {
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
			hitside.bLeft = true;
			setSpeedX(-std::max(abs(getSpeed().x), abs(blockSpeed.x)));
		}
		else if (ballPos.x > boundDP.dot2.x) {
			hitside.bRight = true;
			setSpeedX(std::max(abs(getSpeed().x), abs(blockSpeed.x)));
		}

		if (ballPos.y > boundDP.dot2.y) {
			hitside.bBottom = true;
			setSpeedY(std::max(abs(getSpeed().y), abs(blockSpeed.y)));
		}
		else if (ballPos.y < boundDP.dot1.y) {
			hitside.bTop = true;
			setSpeedY(-std::max(abs(getSpeed().y), abs(blockSpeed.y)));
		}
		bCD = false;
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
		bCD = false;
		return true;
	}
	return false;
}

void MainBall::initialize() {
	setSpeedX((prng(150) % 150 * .01f + 1.5f) * (rng() < 0 ? 1 : -1));
	setSpeedY(-1.5f);
	setActive(false);
	bSettle = true;
}

void MainBall::resettle() {
	if (game::currentGameState != GameState::LEVEL_FINISHED) throw std::invalid_argument("Level not finished.");
	bSettle = false;
}

bool MainBall::isSettle() const {
	return bSettle;
}

MainBall::~MainBall() {
}

void MainBall::determineHitDirect() {
	const Vector2f ballPos = getPosition();
	const float radius = getRadius();
	if (!bBroke) {
		if (hitside.bLeft && hitside.bRight) {
			bBroke = true;
		}
		else if (hitside.bLeft && ballPos.x - radius < 0.0f) {
			bBroke = true;
		}
		else if (hitside.bRight && ballPos.x + radius > LEVEL_WIDTH) {
			bBroke = true;
		}
		else if (hitside.bTop && hitside.bBottom) {
			bBroke = true;
		}
		else if (hitside.bTop && ballPos.y + radius > LEVEL_HEIGHT) {
			bBroke = true;
		}
	}
	if (bBroke) {
		bBroke = false;
		bSettle = false;
		game::currentGameState = GameState::NOT_READY;
	}
	hitside.reset();
}
