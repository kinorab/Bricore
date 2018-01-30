#include "obstacle.h"
#include <iostream>

using namespace std;
using namespace sf;

Obstacle::Obstacle(const size_t number, const vector<Vector2f> &position, const vector<Vector2f> &sideLength)
	: Block(blocks, number, position, sideLength){
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
	}
}

void Obstacle::blockCollision(vector<Block*> blocks){

	try {
		for (size_t i = 0; i < blocks.size(); ++i) {

			for (size_t j = i + 1; j < blocks.size(); ++j) {

				if (blocks.at(i)->getBounds().intersects(blocks.at(j)->getBounds())) {
					blocks.at(i)->setSpeed(blocks.at(i)->getSpeed().x * -1, blocks.at(i)->getSpeed().y * -1);
					blocks.at(j)->setSpeed(blocks.at(j)->getSpeed().x * -1, blocks.at(j)->getSpeed().y * -1);
				}
			}
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}

}

void Obstacle::setColor(const size_t number, const sf::Color c1, const sf::Color c2, const sf::Color c3, const sf::Color c4){

	blocks.at(number)->setVerticeColor(c1, c2, c3, c4);
}

void Obstacle::draw(RenderTarget &target, RenderStates states) const{

	for (size_t i = 0; i < blocks.size(); ++i) {
		states.texture = NULL;
		target.draw(*blocks.at(i), states);
	}
}
