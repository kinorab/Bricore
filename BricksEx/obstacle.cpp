#include "obstacle.h"
#include "ball.h"
#include <iostream>

using namespace std;
using namespace sf;

std::vector <std::unique_ptr<item::Block>> Obstacle::blocks;

// unity of Block-->Obstacle
Obstacle::Obstacle(const size_t number, const vector <Vector2f> &position, const vector <Vector2f> &sideLength) {

	try {
		for (size_t i = 0; i < number; ++i) {
			blocks.push_back(unique_ptr<item::Block>(new item::Block(position.at(i), sideLength.at(i).x, sideLength.at(i).y)));
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::update() {

	for (size_t i = 0; i < blocks.size(); ++i) {
		blockCollision(i);
		blocks.at(i)->update();
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

void Obstacle::reset() {

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
