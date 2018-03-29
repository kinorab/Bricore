#include "define.h"
#include "brick.h"
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace sf;
using namespace item;

Brick::Brick(const size_t rowCount, const float wid, const float hei, const Vector2f &interval, const float frameSize) {

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
			amount = static_cast<size_t>((LEVEL_WIDTH - getInterval().x) / (getInterval().x + getSideLength().x + frame * 2));
			bricks.resize(rowCount * amount);

			if (getBricksSize() == rowCount * amount) {
				changeEntity = true;
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

void Brick::loadImage(const string fileName) {
	levelImage.emplace(fileName, new Texture());
	levelImage.at(fileName)->loadFromFile(fileName);
}

void Brick::deleteImage(const string fileName) {
	auto image = levelImage.find(fileName);
	if (image != levelImage.end()) {
		levelImage.erase(image);
	}
	else {
		cout << "Image not found." << endl;
	}
}

void Brick::displayImage(const string fileName) {
	for (size_t i = 0; i < getBricksSize(); ++i) {
		bricks.at(i)->setTexture(levelImage.at(fileName));
	}
}

void Brick::setBrickColor(const Color &color) {
	for (size_t i = 0; i < getBricksSize(); ++i) {
		bricks.at(i)->setFillColor(color);
	}
}

void Brick::setFrameColor(const Color &color) {
	if (frame > 0.0f) {
		for (size_t i = 0; i < getBricksSize(); ++i) {
			bricks.at(i)->setOutlineColor(color);
		}
	}
	else {
		cout << "Brick frames do not exist." << endl;
	}
}

void Brick::setRowAmount(const int row) {

	if (row > 0) {
		bricks.resize(row * amount);
		changeEntity = true;
		settlePlace();
	}
	else {
		cout << "Invalid bricks setting." << endl;
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

void Brick::update(Ball &ball) {

	for (size_t i = 0; i < getBricksSize(); ++i) {

		FloatRect brickBounds = bricks.at(i)->getGlobalBounds();
		if (ball.ballCollided(brickBounds)) {
			bricks.erase(bricks.begin() + i);
			--i;
		}
	}
}

void Brick::reset(const size_t rowCount, const float wid, const float hei
	, const Vector2f &interval, const float frameSize) {

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
			amount = static_cast<size_t>((LEVEL_WIDTH - getInterval().x) / (getInterval().x + getSideLength().x + frame * 2));
			bricks.resize(rowCount * amount);

			if (getBricksSize() == rowCount * amount) {
				changeEntity = true;
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

void Brick::reset(const size_t rowCount) {

	try {
		bricks.resize(rowCount * amount);

		if (getBricksSize() == rowCount * amount) {
			changeEntity = true;
			settlePlace();
		}
		else {
			throw out_of_range("The subscripts are out of range.");
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

const bool Brick::isEmpty() const {
	return bricks.empty();
}

const size_t Brick::getBricksSize() const {
	return bricks.size();
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

	static float whiteSpace = (LEVEL_WIDTH - ((interval.x + sideLength.x + frame * 2) * amount + interval.x)) / 2;
	// if window's size().x cannot be filled with full screen, remain the white space of bound
	static Vector2f initialPos(whiteSpace + interval.x + sideLength.x / 2 + frame, interval.y + sideLength.y / 2 + frame);
	static Vector2f tempPos = Vector2f(initialPos.x, initialPos.y);
	static size_t tempCount = 1;

	try {
		if (changeEntity == true) {
			for (size_t i = 0; i < bricks.size(); ++i) {
				bricks.at(i) = unique_ptr<RectangleShape>(new RectangleShape(Vector2f(sideLength.x, sideLength.y)));
				if (frame > 0.0f) {
					bricks.at(i)->setOutlineThickness(frame);
					bricks.at(i)->setOutlineColor(Color::Black);
				}
				// center origin position in every brick
				bricks.at(i)->setOrigin(Vector2f(bricks.at(i)->getSize().x / 2, bricks.at(i)->getSize().y / 2));
			}
			// cover all attributes again
			whiteSpace = (LEVEL_WIDTH - ((interval.x + sideLength.x + frame * 2) * amount + interval.x)) / 2;
			initialPos = Vector2f(whiteSpace + interval.x + sideLength.x / 2 + frame, interval.y + sideLength.y / 2 + frame);
			tempPos = Vector2f(initialPos.x, initialPos.y);
			changeEntity = false;
		}

		// ensure that total with the intervals should not be out of screen
		if (whiteSpace >= 0.0f) {
			// start placing bricks array
			for (size_t i = 0; i < bricks.size(); ++i) {

				bricks.at(i)->setPosition(tempPos);
				if (tempCount < amount) {
					tempPos += Vector2f(interval.x + bricks.at(i)->getGlobalBounds().width, 0);
					++tempCount;
				}
				else {
					tempPos = Vector2f(initialPos.x, tempPos.y + interval.y + bricks.at(i)->getGlobalBounds().height);
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

	for (size_t i = 0; i < getBricksSize(); ++i) {
		states.texture = bricks.at(i)->getTexture();
		target.draw(*bricks.at(i), states);
	}
}
