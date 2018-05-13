#include "obstacle.h"
#include "define.h"
#include "block.h"
#include "intersects.h"
#include "LVDeploy.h"
#include "ball.h"
#include <iostream>

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
	try {
		if (position.size() == sideLength.size()) {
			blocks.resize(position.size());
			for (size_t i = 0; i < blocks.size(); ++i) {
				blocks.at(i) = shared_ptr<item::Block>(new item::Block(position.at(i), sideLength.at(i).x, sideLength.at(i).y));
			}
			GameState::obstacleArea = RectangleShape(Vector2f(LEVEL_WIDTH
				, LEVEL_HEIGHT - (GameState::playerArea.getSize().y + GameState::bricksArea.getSize().y + 2 * AREAINTERVAL)));
			GameState::obstacleArea.setPosition(Vector2f(0.0f, GameState::bricksArea.getSize().y + AREAINTERVAL));
		}
		else {
			throw out_of_range("Position size not equal to side-length size.");
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::reset(): " << ex.what() << endl;
	}
}


void Obstacle::update(item::Ball &ball) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i)->update();
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

void Obstacle::preUpdate(item::Ball & ball) {
	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i)->update();
		blocksCollision(i);
	}
	for (size_t ballN = 0; ballN < ball.getBallsAmount(); ++ballN) {
		if (ball.isBallEnteredObstacleArea(ballN)) {
			for (size_t blocksN = 0; blocksN < blocks.size(); ++blocksN) {
				ball.ballCollidedObstaclePre(ballN, blocksN, getDP(blocksN), getSpeed(blocksN));
			}
		}
	}
}

void Obstacle::setBlockColor(const size_t number, const Color &c1, const Color &c2, const Color &c3, const Color &c4) {

	try {
		blocks.at(number)->setVerticeColor(c1, c2, c3, c4);
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setBlockColor(): " << ex.what() << endl;
	}
}

void Obstacle::setBlockColor(const size_t number, const Color &color) {

	try {
		blocks.at(number)->setVerticeColor(color);
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setBlockColor(): " << ex.what() << endl;
	}
}

void Obstacle::setAllColor(const vector<Color>& color) {

	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->setVerticeColor(color.at(i));
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setAllColor(): " << ex.what() << endl;
	}
}

void Obstacle::setAllVerticeColor(const std::vector<sf::Color>& vertice) {
	try {
		for (size_t i = 0, j = 1; i < blocks.size(); ++i, ++j) {
			blocks.at(i)->setVerticeColor(vertice.at(4 * j - 4), vertice.at(4 * j - 3), vertice.at(4 * j - 2), vertice.at(4 * j - 1));
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setAllVerticeColor(): " << ex.what() << endl;
	}
}

void Obstacle::setBlockSpeed(const size_t number, const float speedX, const float speedY) {

	try {
		blocks.at(number)->setSpeed(speedX, speedY);
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setBlockSpeed(): " << ex.what() << endl;
	}
}

void Obstacle::setBlockSpeed(const size_t number, const Vector2f & speed) {

	try {
		blocks.at(number)->setSpeed(speed);
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setBlockSpeed(): " << ex.what() << endl;
	}
}

void Obstacle::setAllSpeed(const vector <Vector2f> &speed) {

	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->setSpeed(speed.at(i));
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::setAllSpeed(): " << ex.what() << endl;
	}
}

void Obstacle::restart() {

	try {
		if (!GameState::ready) {
			for (size_t i = 0; i < blocks.size(); ++i) {
				blocks.at(i)->resetPosition();
			}
			GameState::ready = true;
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::restart(): " << ex.what() << endl;
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

	try {
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
	catch (out_of_range &ex) {
		cout << "Out_of_range in Obstacle::blockCollision(): " << ex.what() << endl;
	}

}
