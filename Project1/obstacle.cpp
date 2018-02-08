#include "obstacle.h"
#include "define.h"
#include <iostream>

using namespace std;
using namespace sf;
using namespace item;

// unity of Block-->Obstacle
Obstacle::Obstacle(const size_t number, const vector <Vector2f> &position, const vector <Vector2f> &sideLength) {

	blocks.resize(number);
	try {
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i) = new Block(position.at(i), sideLength.at(i).x, sideLength.at(i).y);
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Obstacle::enable(CircleShape &ball, float &ballSpeedX, float &ballSpeedY) {

	for (size_t i = 0; i < blocks.size(); ++i) {
		FloatRect blockBounds = blocks.at(i)->getBounds();
		FloatRect ballBounds = ball.getGlobalBounds();
		FloatRect leftBlock(Vector2f(blockBounds.left, blockBounds.top + ball.getRadius())
			, Vector2f(ballBounds.width, blockBounds.height - ball.getRadius() * 2));
		FloatRect rightBlock(Vector2f(blockBounds.left + blockBounds.width - ballBounds.width, blockBounds.top + ball.getRadius())
			, Vector2f(ballBounds.width, blockBounds.height - ball.getRadius() * 2));
		FloatRect topBlock(Vector2f(blockBounds.left + ball.getRadius(), blockBounds.top)
			, Vector2f(blockBounds.width - ball.getRadius() * 2, ballBounds.height));
		FloatRect bottomBlock(Vector2f(blockBounds.left + ball.getRadius(), blockBounds.top + blockBounds.height - ballBounds.height)
			, Vector2f(blockBounds.width - ball.getRadius() * 2, ballBounds.height));

		if (ballBounds.intersects(leftBlock)) {
			ballSpeedX = -abs(ballSpeedX);
		}
		else if (ballBounds.intersects(rightBlock)) {
			ballSpeedX = abs(ballSpeedX);
		}

		if (ballBounds.intersects(topBlock)) {
			ballSpeedY = -abs(ballSpeedY);
		}
		else if (ballBounds.intersects(bottomBlock)) {
			ballSpeedY = abs(ballSpeedY);
		}
		blockCollision(i);
		move(i);
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
		for (size_t i = 0; i < blocks.size(); ++i) {
			blocks.at(i)->resetPosition();
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
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

void Obstacle::move(const size_t number) {

	try {
		blocks.at(number)->move();
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}