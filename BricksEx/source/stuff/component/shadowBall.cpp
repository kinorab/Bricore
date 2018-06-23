#include "shadowBall.h"
#include "mainBall.h"
#include "block.h"
#include "brick.h"
#include "../../definition/intersects.h"
#include "../../definition/gameState.h"

using namespace item;
using namespace sf;

ShadowBall::ShadowBall(const MainBall * main) {
	setPosition(main->getPosition());
	setSpeedX(main->getSpeed().x * ((prng(50) % 50 + 50) * .01f * (rng() < 0 ? -1 : 1)));
	setSpeedY(main->getSpeed().y * ((prng(20) % 20 + 80) * .01f * (rng() < 0 ? -1 : 1)));
}

bool ShadowBall::isCollidedObstacle(const Block * block) {
	const float radius = getRadius();
	const Vector2f ballPos(getPosition());
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

bool ShadowBall::isCollidedWall(const Brick * brick) {
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

ShadowBall::~ShadowBall() {
}

void ShadowBall::determineUpdate() {
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
	left = false;
	right = false;
	top = false;
	bottom = false;
}
