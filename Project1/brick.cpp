#include "define.h"
#include "brick.h"
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace sf;

// user set the brick array manually
Brick::Brick(const size_t row, const size_t col, const float wid, const float hei, const Vector2f &interval, const float frameSize) {

	try {
		if (wid <= 0.0f || hei <= 0.0f
			|| interval.x < 0.0f || interval.y < 0.0f
			|| frameSize < 0.0f) {
			throw domain_error("Invaild brick initialization.");
		}
		else if (col * (wid + frameSize * 2) + interval.x * (col + 1) > STAGE_WIDTH
			|| row * (hei + frameSize * 2) + interval.y * (row + 1) > STAGE_HEIGHT) {
			throw domain_error("Invaild brick initialization.");
		}
		else {
			area.resize(row * col);
			amount = col;
			sideLength = Vector2f(wid, hei);
			frame = frameSize;
			this->interval = interval;

			if (getAreaSize() == row * amount) {
				settlePlace();
			}
			else {
				throw out_of_range("The subscripts are out of range.");
			}
		}
	}
	catch (domain_error &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

// auto full up the window
Brick::Brick(const size_t rowAmount, const float wid, const float hei, const Vector2f &interval, const float frameSize) {

	try {
		if (wid <= 0.0f || hei <= 0.0f
			|| interval.x < 0.0f || interval.y < 0.0f
			|| frameSize < 0.0f) {
			throw domain_error("Invaild brick initialization.");
		}
		else {
			sideLength = Vector2f(wid, hei);
			frame = frameSize;
			this->interval = interval;
			amount = static_cast<size_t>((STAGE_WIDTH - getInterval().x) / (getInterval().x + getSideLength().x));
			area.resize(rowAmount * amount);

			if (getAreaSize() == rowAmount * amount) {
				settlePlace();
			}
			else {
				throw out_of_range("The subscripts are out of range.");
			}
		}
	}
	catch (domain_error &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Brick::loadImage(Texture *image) {
	for (size_t i = 0; i < getAreaSize(); ++i) {
		area.at(i).setTexture(image);
	}
}

void Brick::setBrickColor(const Color &color) {
	for (size_t i = 0; i < getAreaSize(); ++i) {
		area.at(i).setFillColor(color);
	}
}

void Brick::setFrameColor(const Color &color) {
	if (frame > 0.0f) {
		for (size_t i = 0; i < getAreaSize(); ++i) {
			area.at(i).setOutlineColor(color);
		}
	}
	else {
		cout << "Brick frames do not exist." << endl;
	}
}

void Brick::setRowAmount(const int row) {

	if (row > 0) {
		area.resize(row * amount);
		changeEntity = true;
		settlePlace();
	}
	else {
		cout << "Invalid area setting." << endl;
	}
}

void Brick::setSideLength(const Vector2f & sideLength) {

	if (sideLength.x > 0 && sideLength.y > 0) {
		this->sideLength = sideLength;
		changeEntity = true;
		settlePlace();
	}
	else {
		cout << "Invalid side-length setting." << endl;
	}
}

void Brick::setSideLength(const float wid, const float hei) {

	if (wid > 0 && hei > 0) {
		sideLength = Vector2f(wid, hei);
		changeEntity = true;
		settlePlace();
	}
	else {
		cout << "Invalid side-length setting." << endl;
	}
}

void Brick::setInterval(const Vector2f &interval) {

	if (interval.x >= 0.0f && interval.y >= 0.0f) {
		this->interval = interval;
		settlePlace();
	}
	else {
		cout << "Invalid interval setting." << endl;
	}
}

void Brick::setInterval(const float x, const float y) {

	if (x >= 0.0f && y >= 0.0f) {
		interval = Vector2f(x, y);
		settlePlace();
	}
	else {
		cout << "Invalid interval setting." << endl;
	}
}

void Brick::setFrameSize(const float frameSize) {

	if (frameSize >= 0.0f) {
		frame = frameSize;
		changeEntity = true;
		settlePlace();
	}
	else {
		cout << "Invalid frame size setting." << endl;
	}
}

void Brick::collisionBroke(CircleShape &ball, float &speedX, float &speedY) {

	for (size_t i = 0; i < getAreaSize(); ++i) {

		FloatRect brickBounds = area.at(i).getGlobalBounds();
		FloatRect ballBounds = ball.getGlobalBounds();
		FloatRect leftBlock = FloatRect(Vector2f(brickBounds.left, brickBounds.top + ball.getRadius()), Vector2f(1, brickBounds.height - ball.getRadius() * 2));
		FloatRect rightBlock = FloatRect(Vector2f(brickBounds.left + brickBounds.width - 1, brickBounds.top + ball.getRadius()), Vector2f(1, brickBounds.height - ball.getRadius() * 2));
		FloatRect topBlock = FloatRect(Vector2f(brickBounds.left + ball.getRadius(), brickBounds.top), Vector2f(brickBounds.width - ball.getRadius() * 2, 1));
		FloatRect bottomBlock = FloatRect(Vector2f(brickBounds.left + ball.getRadius(), brickBounds.top + brickBounds.height - 1), Vector2f(brickBounds.width - ball.getRadius() * 2, 1));

		// temporary setting
		if (ballBounds.intersects(bottomBlock)) {
			speedY = abs(speedY);
			 area.erase(area.begin() + i);
		}
		else if (ballBounds.intersects(leftBlock)) {
			speedX = -abs(speedX);
			area.erase(area.begin() + i);
		}
		else if (ballBounds.intersects(rightBlock)) {
			speedX = abs(speedX);
			area.erase(area.begin() + i);
		}
		else if (ballBounds.intersects(topBlock)) {
			speedY = -abs(speedY);
			area.erase(area.begin() + i);
		}

	}
}

const size_t Brick::getAreaSize() const {
	return area.size();
}

const Vector2f & Brick::getSideLength() const {
	return sideLength;
}

const Vector2f & Brick::getInterval() const {
	return interval;
}

const float Brick::getFrameSize() const {
	return frame;
}

void Brick::settlePlace() {

	static float whiteSpace = (STAGE_WIDTH - ((interval.x + sideLength.x + frame * 2) * amount + interval.x)) / 2;
	// if window's size().x cannot be filled with full screen, remain the white space of bound
	static Vector2f initialPos(whiteSpace + interval.x + sideLength.x / 2 + frame, interval.y + sideLength.y / 2 + frame);
	static Vector2f tempPos = Vector2f(initialPos.x, initialPos.y);
	static size_t tempCount = 1;

	try {
		if (changeEntity == true) {
			for (size_t i = 0; i < area.size(); ++i) {
				area.at(i).setSize(Vector2f(sideLength.x, sideLength.y));
				if (frame > 0.0f) {
					area.at(i).setOutlineThickness(frame);
					// if frames exist, the default color is set black
					area.at(i).setOutlineColor(Color::Black);
				}
				// center origin position in every brick
				area.at(i).setOrigin(Vector2f(area.at(i).getSize().x / 2, area.at(i).getSize().y / 2));
			}
			// cover all attributes again
			whiteSpace = (STAGE_WIDTH - ((interval.x + sideLength.x + frame * 2) * amount + interval.x)) / 2;
			initialPos = Vector2f(whiteSpace + interval.x + sideLength.x / 2 + frame, interval.y + sideLength.y / 2 + frame);
			tempPos = Vector2f(initialPos.x, initialPos.y);
			changeEntity = false;
		}

		// ensure that total with the intervals should not be out of screen
		if (whiteSpace >= 0.0f) {
			// start placing area array
			for (size_t i = 0; i < area.size(); ++i) {

				area.at(i).setPosition(tempPos);
				if (tempCount < amount) {
					tempPos += Vector2f(interval.x + area.at(i).getGlobalBounds().width, 0);
					++tempCount;
				}
				else {
					tempPos = Vector2f(initialPos.x, tempPos.y + interval.y + area.at(i).getGlobalBounds().height);
					tempCount = 1;
				}
			}
		}
		else {
			cout << "Intervals are too long to place." << endl;
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Brick::draw(RenderTarget &target, RenderStates states) const {

	for (size_t i = 0; i < getAreaSize(); ++i) {
		states.texture = area.at(i).getTexture();
		target.draw(area.at(i), states);
	}
}
