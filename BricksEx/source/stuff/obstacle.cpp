#include "obstacle.h"
#include "block.h"
#include "ball.h"
#include "../gameSys/LVDeploy.h"
#include "../definition/define.h"
#include "../definition/intersects.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// unity of Block-->Obstacle
Obstacle::Obstacle() {
	reset(LVDeploy::getBlockPD(), LVDeploy::getBlockSLD());
	setAllVerticeColor(LVDeploy::getBlockCD());
	setAllSpeed(LVDeploy::getBlockSD());
}

Obstacle::Obstacle(const Obstacle & copy) {
	blocks.clear();
	std::for_each(copy.blocks.begin(), copy.blocks.end()
		, [&](const std::shared_ptr<item::Block> element) {
		blocks.push_back(std::make_shared<item::Block>(*element));
	});
}

void Obstacle::reset(const vector <Vector2f> & position, const vector <Vector2f> & sideLength) {

	if (position.size() != sideLength.size()) {
		throw out_of_range("Position size not equal to side-length size.");
	}

	blocks.resize(position.size());
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i) = shared_ptr<item::Block>(new item::Block(position.at(i), sideLength.at(i).x, sideLength.at(i).y));
	}

	GameState::obstacleArea = RectangleShape(Vector2f(LEVEL_WIDTH
		, LEVEL_HEIGHT - (GameState::playerArea.getSize().y + GameState::bricksArea.getSize().y + 2 * AREAINTERVAL)));
	GameState::obstacleArea.setPosition(Vector2f(0.0f, GameState::bricksArea.getSize().y + AREAINTERVAL));
}


void Obstacle::update(item::Ball &ball, const float intervalRate) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i)->update(intervalRate);
		blocksCollision(i);
	}
	for (size_t ballN = 0; ballN < ball.getBallsAmount(); ++ballN) {
		if (ball.isBallEnteredObstacleArea(ballN)) {
			for (size_t blocksN = 0; blocksN < blocks.size(); ++blocksN) {
				ball.ballCollidedObstacle(ballN, blocksN, getDP(blocksN), getSpeed(blocksN));
			}
		}
	}
	if (GameState::finishLevel) {
		reset(LVDeploy::getBlockPD(), LVDeploy::getBlockSLD());
		setAllVerticeColor(LVDeploy::getBlockCD());
		setAllSpeed(LVDeploy::getBlockSD());
	}
}

void Obstacle::setBlockColor(const size_t number, const Color &c1, const Color &c2, const Color &c3, const Color &c4) {
	blocks.at(number)->setVerticeColor(c1, c2, c3, c4);
}

void Obstacle::setBlockColor(const size_t number, const Color &color) {
	blocks.at(number)->setVerticeColor(color);
}

void Obstacle::setAllColor(const vector<Color>& color) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i)->setVerticeColor(color.at(i));
	}
}

void Obstacle::setAllVerticeColor(const std::vector<sf::Color>& vertice) {
	for (size_t i = 0, j = 1; i < blocks.size(); ++i, ++j) {
		blocks.at(i)->setVerticeColor(vertice.at(4 * j - 4), vertice.at(4 * j - 3), vertice.at(4 * j - 2), vertice.at(4 * j - 1));
	}
}

void Obstacle::setBlockSpeed(const size_t number, const float speedX, const float speedY) {
	blocks.at(number)->setSpeed(speedX, speedY);
}

void Obstacle::setBlockSpeed(const size_t number, const Vector2f & speed) {
	blocks.at(number)->setSpeed(speed);
}

void Obstacle::setAllSpeed(const vector <Vector2f> &speed) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i)->setSpeed(speed.at(i));
	}
}

void Obstacle::restart() {
	if (!GameState::ready) {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->resetPosition();
		}
		GameState::ready = true;
	}
}

const Vector2f & Obstacle::getSpeed(const size_t number) const {
	return blocks.at(number)->getSpeed();
}

const size_t Obstacle::getBlocksAmount() const {
	return blocks.size();
}

const sys::DPointf Obstacle::getDP(const size_t number) const {
	return blocks.at(number)->getDP();
}

Obstacle & Obstacle::operator=(const Obstacle &) = default;

void Obstacle::draw(RenderTarget &target, RenderStates states) const {
	states.texture = nullptr;
	for (size_t i = 0; i < blocks.size(); ++i) {
		target.draw(*blocks.at(i), states);
	}
}

void Obstacle::blocksCollision(const size_t number) {

	for (size_t j = number + 1; j < blocks.size(); ++j) {

		if (game::INCIntersects(blocks.at(number)->getDP(), blocks.at(j)->getDP())) {

			const Vector2f APos(blocks.at(number)->getCenterPosition());
			const Vector2f BPos(blocks.at(j)->getCenterPosition());
			const Vector2f ASpeed(blocks.at(number)->getSpeed());
			const Vector2f BSpeed(blocks.at(j)->getSpeed());
			if (APos.x > BPos.x) {
				if (APos.y > BPos.y) {
					blocks.at(number)->setSpeed(abs(ASpeed.x), abs(ASpeed.y));
					blocks.at(j)->setSpeed(-abs(BSpeed.x), -abs(BSpeed.y));
				}
				else {
					blocks.at(number)->setSpeed(abs(ASpeed.x), -abs(ASpeed.y));
					blocks.at(j)->setSpeed(-abs(BSpeed.x), abs(BSpeed.y));
				}
			}
			else {
				if (APos.y > BPos.y) {
					blocks.at(number)->setSpeed(-abs(ASpeed.x), abs(ASpeed.y));
					blocks.at(j)->setSpeed(abs(BSpeed.x), -abs(BSpeed.y));
				}
				else {
					blocks.at(number)->setSpeed(-abs(ASpeed.x), -abs(ASpeed.y));
					blocks.at(j)->setSpeed(abs(BSpeed.x), abs(BSpeed.y));
				}
			}
		}
	}
}
