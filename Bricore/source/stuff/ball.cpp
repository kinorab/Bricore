#include "ball.h"
#include "player.h"
#include "subPlayer.h"
#include "component/mainBall.h"
#include "component/shadowBall.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../definition/intersects.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

using namespace sf;
using namespace item;

Ball::Ball(const std::shared_ptr<game::Level> level)
	: bMultiple(false)
	, bCollision(false)
	, mainBall(new MainBall)
	, m_level(std::move(level)) {
}

void Ball::update(const float updateRatio) {
	const sys::DPointf playerDP(c_player->getDP());
	const float playerSpeed = c_player->getSpeed();
	mainBall->move(playerDP, playerSpeed, updateRatio);
	for (size_t i = 0; i < shadowBalls.size(); ++i) {
		shadowBalls[i]->move(playerDP, playerSpeed, updateRatio);
		if (shadowBalls[i]->isBroke()) {
			// remove need to be first
			removeChild({ shadowBalls[i] });
			shadowBalls.erase(shadowBalls.begin() + i);
		}
		if (bMultiple) {
			ballsCollision(i);
		}
	}
}

void Ball::resetCopyTarget(const std::shared_ptr<const Player> player
	, const std::shared_ptr<const SubPlayer> subPlayer) {
	c_player = std::move(player);
	c_subPlayer = std::move(subPlayer);
	followPlayer();
}

void Ball::initializeBall() {
	if (!mainBall->isSettle()) {
		removeAllChildren();
		addChild({ mainBall });
		shadowBalls.clear();
		mainBall->initialize();
	}
	else if (game::currentGameState == GameState::LEVEL_FINISHED) {
		mainBall->resettle();
		game::currentGameState = GameState::NOT_READY;
	}
}

void Ball::followPlayer() {
	sf::Vector2f pos{ c_player->getTopCenterPos() };
	mainBall->setPosition(pos.x, pos.y - mainBall->getRadius() - 1.f);
}

std::vector<std::shared_ptr<Globular>> Ball::enteredObstacleArea() const {
	std::vector<std::shared_ptr<Globular>> temp;
	if (mainBall->isEnteredObstacleArea()) {
		temp.push_back(mainBall);
	}
	std::for_each(shadowBalls.begin(), shadowBalls.end()
		, [&](const std::shared_ptr<Globular> &element) {
		if (element->isEnteredObstacleArea()) {
			temp.push_back(element);
		}
	});
	return temp;
}

std::vector<std::shared_ptr<item::Globular>> Ball::enteredWallArea() const {
	std::vector<std::shared_ptr<Globular>> temp;
	if (mainBall->isEnteredWallArea()) {
		temp.push_back(mainBall);
	}
	std::for_each(shadowBalls.begin(), shadowBalls.end()
		, [&](const std::shared_ptr<Globular> &element) {
		if (element->isEnteredWallArea()) {
			temp.push_back(element);
		}
	});
	return temp;
}

void Ball::ballDivided(const size_t numbers) {
	for (size_t i = 0; i < numbers; ++i) {
		auto shadowBall = std::make_shared<ShadowBall>(mainBall.get());
		addChild({ shadowBall });
		shadowBalls.push_back(shadowBall);
	}
	bCollision = false;
	bMultiple = true;
}

float Ball::getMainBallRadius() const {
	return mainBall->getRadius();
}

const Vector2f & Ball::getMainBallPosition() const {
	return mainBall->getPosition();
}

size_t Ball::getBallsAmount() const {
	return shadowBalls.size() + 1;
}

Ball::~Ball() {
	removeAllChildren(true);
	removeAllListener();
}

void Ball::draw(RenderTarget &target, RenderStates states) const {
	Container::draw(target, states);
}

void Ball::ballsCollision(const size_t number) {
	std::vector<std::shared_ptr<Globular>> balls({ mainBall });
	for (auto element : shadowBalls) {
		balls.push_back(element);
	}
	for (size_t j = number + 1; j < balls.size(); ++j) {
		const Vector2f APos = balls[number]->getPosition();
		const float AR = balls[number]->getRadius();
		const Vector2f BPos = balls[j]->getPosition();
		const float BR = balls[j]->getRadius();
		if (bCollision && sys::ballsIntersects(APos, AR, BPos, BR)) {
			const float avarageSpeedX = (abs(balls[number]->getSpeed().x) + abs(balls[j]->getSpeed().x)) / 2;
			const float ASpeedY = balls[number]->getSpeed().y;
			const float BSpeedY = balls[j]->getSpeed().y;
			balls[number]->restartClock();
			balls[j]->restartClock();
			if (APos.x > BPos.x) {
				if (APos.y > BPos.y) {
					balls[number]->setSpeed(Vector2f(abs(avarageSpeedX), abs(ASpeedY)));
					balls[j]->setSpeed(Vector2f(-abs(avarageSpeedX), -abs(BSpeedY)));
				}
				else {
					balls[number]->setSpeed(Vector2f(abs(avarageSpeedX), -abs(ASpeedY)));
					balls[j]->setSpeed(Vector2f(-abs(avarageSpeedX), abs(BSpeedY)));
				}
			}
			else {
				if (APos.y > BPos.y) {
					balls[number]->setSpeed(Vector2f(-abs(avarageSpeedX), abs(ASpeedY)));
					balls[j]->setSpeed(Vector2f(abs(avarageSpeedX), -abs(BSpeedY)));
				}
				else {
					balls[number]->setSpeed(Vector2f(-abs(avarageSpeedX), -abs(ASpeedY)));
					balls[j]->setSpeed(Vector2f(abs(avarageSpeedX), abs(BSpeedY)));
				}
			}
		}
		else if (sys::ballsDistance(APos, AR, BPos, BR) < 2.f) {
			return;
		}
	}
	if (!bCollision) {
		bCollision = true;
	}
}
