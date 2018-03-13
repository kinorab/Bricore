#include "obstacle.h"
#include "define.h"
#include <iostream>

using namespace std;
using namespace sf;

// unity of Block-->Obstacle
Obstacle::Obstacle(const size_t number, const vector <Vector2f> &position, const vector <Vector2f> &sideLength) {

	blocks.resize(number);
	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i) = unique_ptr<Block>(new Block(position.at(i), sideLength.at(i).x, sideLength.at(i).y));
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::update(item::Ball &ball) {

	for (size_t i = 0; i < blocks.size(); ++i) {
		blockCollision(i);
		blocks.at(i)->update(ball);
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

void Obstacle::resettle() {

	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->resetPosition();
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

const sf::Vector2f & Obstacle::getBlockSpeed(const size_t number) const {
	return blocks.at(number)->getSpeed();
}

const size_t Obstacle::getBlocksAmount() const {
	return blocks.size();
}

void Obstacle::draw(RenderTarget &target, RenderStates states) const {

	for (size_t i = 0; i < blocks.size(); ++i) {
		states.texture = NULL;
		target.draw(*blocks.at(i), states);
	}
}

void Obstacle::blockCollision(const size_t number) {

	try {
		for (size_t j = number + 1; j < blocks.size(); ++j) {

			if (blocks.at(number)->getBounds().intersects(blocks.at(j)->getBounds())) {

				blocks.at(number)->setSpeed(blocks.at(number)->getSpeed().x * -1, blocks.at(number)->getSpeed().y * -1);
				blocks.at(j)->setSpeed(blocks.at(j)->getSpeed().x * -1, blocks.at(j)->getSpeed().y * -1);
			}
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}

}
