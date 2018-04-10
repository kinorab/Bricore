#include "obstacle.h"
#include "define.h"
#include "intersects.h"
#include "ball.h"
#include "brick.h"
#include "player.h"
#include <iostream>

using namespace std;
using namespace sf;

RectangleShape Obstacle::blocksArea;
std::vector <std::unique_ptr<item::Block>> Obstacle::blocks;

// unity of Block-->Obstacle
Obstacle::Obstacle(const vector <Vector2f> &position, const vector <Vector2f> &sideLength) {

	try {
		if (position.size() == sideLength.size()) {
			for (size_t i = 0; i < position.size(); ++i) {
				blocks.push_back(unique_ptr<item::Block>(new item::Block(position.at(i), sideLength.at(i).x, sideLength.at(i).y)));
			}
			setBlocksAreaDP(sys::DPointf(Vector2f(0.0f, item::Brick::getBrickAreaDP().dot2.y + AREAINTERVAL)
				, Vector2f(LEVEL_WIDTH, Player::getPlayerAreaDP().dot1.y - AREAINTERVAL)));
		}
		else {
			throw out_of_range("Position size not equal to side-length size.");
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::update() {

	for (size_t i = 0; i < blocks.size(); ++i) {
		blocks.at(i)->update();
		blockCollision(i);
	}
	for (size_t i = 0; i < item::Ball::getBallsAmount(); ++i) {
		if (item::Ball::isBallEnteredBlocksArea(i)) {
			for (size_t j = 0; j < blocks.size(); ++j) {
				item::Ball::ballCollided(i, j);
			}
		}
	}
}

void Obstacle::setBlockColor(const size_t number, const Color &c1, const Color &c2, const Color &c3, const Color &c4) {

	try {
		blocks.at(number)->setVerticeColor(c1, c2, c3, c4);
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::setBlockColor(const size_t number, const Color &color) {

	try {
		blocks.at(number)->setVerticeColor(color);
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::setAllColor(const vector<Color>& color) {

	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->setVerticeColor(color.at(i));
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::setBlockSpeed(const size_t number, const float speedX, const float speedY) {

	try {
		blocks.at(number)->setSpeed(speedX, speedY);
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::setBlockSpeed(const size_t number, const Vector2f & speed) {

	try {
		blocks.at(number)->setSpeed(speed);
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::setAllSpeed(const vector <Vector2f> &speed) {

	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->setSpeed(speed.at(i));
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::setBlocksAreaDP(const sys::DPointf & DP) {
	blocksArea.setSize(DP.dot2 - DP.dot1);
	blocksArea.setPosition(DP.dot1);
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
		cout << "Exception: " << ex.what() << endl;
	}
}

const Vector2f & Obstacle::getBlockSpeed(const size_t number) {
	return blocks.at(number)->getSpeed();
}

const size_t Obstacle::getBlocksAmount() {
	return blocks.size();
}

const sys::DPointf Obstacle::getDP(const size_t number) {
	return blocks.at(number)->getDP();
}

const sys::DPointf Obstacle::getBlocksAreaDP() {
	const Vector2f LT(blocksArea.getGlobalBounds().left, blocksArea.getGlobalBounds().top);
	const Vector2f RB(LT.x + blocksArea.getGlobalBounds().width, LT.y + blocksArea.getGlobalBounds().height);
	return sys::DPointf(LT, RB);
}

void Obstacle::draw(RenderTarget &target, RenderStates states) const {
	states.texture = nullptr;
	for (size_t i = 0; i < blocks.size(); ++i) {
		target.draw(*blocks.at(i), states);
	}
}

void Obstacle::blockCollision(const size_t number) {

	try {
		for (size_t j = number + 1; j < blocks.size(); ++j) {

			if (game::INCIntersects(blocks.at(number)->getDP(), blocks.at(j)->getDP())) {

				blocks.at(number)->setSpeed(blocks.at(number)->getSpeed().x * -1, blocks.at(number)->getSpeed().y * -1);
				blocks.at(j)->setSpeed(blocks.at(j)->getSpeed().x * -1, blocks.at(j)->getSpeed().y * -1);
			}
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}

}
