#include "brick.h"
#include "ball.h"
#include "define.h"
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace sf;
using namespace item;

vector <unique_ptr<RectangleShape>> Brick::bricks;
map <string, Texture *> Brick::levelImage;
size_t Brick::amount;
size_t Brick::rowCount;
float Brick::frame;
Vector2f Brick::interval;
Vector2f Brick::sideLength;
Vector2f Brick::whiteSpace(0.0f, 0.0f);
bool Brick::changeEntity(false);
RectangleShape Brick::bricksArea;

Brick::Brick(const size_t rowCount, const float wid, const float hei, const Vector2f &interval, const float frameSize, const float whiteSpaceY) {

	try {
		if (wid <= 0.0f || hei <= 0.0f
			|| interval.x < 0.0f || interval.y < 0.0f
			|| frameSize < 0.0f || whiteSpaceY < 0.0f) {
			throw invalid_argument("Invaild brick initialization.");
		}
		else {
			sideLength = Vector2f(wid, hei);
			this->rowCount = rowCount;
			frame = frameSize;
			this->interval = interval;
			amount = static_cast<size_t>((LEVEL_WIDTH - getInterval().x) / (getInterval().x + getSideLength().x + frame * 2));
			whiteSpace.x = (LEVEL_WIDTH - ((this->interval.x + sideLength.x + frame * 2) * amount - this->interval.x)) / 2;
			whiteSpace.y = whiteSpaceY;
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
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
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
	try {
		if (image != levelImage.end()) {
			levelImage.erase(image);
		}
		else {
			domain_error("Image not found.");
		}
	}
	catch (domain_error &ex) {
		cout << "Domain_error: " << ex.what() << endl;
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
	try {
		if (frame > 0.0f) {
			for (size_t i = 0; i < getBricksSize(); ++i) {
				bricks.at(i)->setOutlineColor(color);
			}
		}
		else {
			invalid_argument("Brick frames do not exist.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::setRowAmount(const int row) {
	try {
		if (row > 0) {
			bricks.resize(row * amount);
			changeEntity = true;
			settlePlace();
		}
		else {
			invalid_argument("Row cannot be negative.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::setSideLength(const Vector2f & sideLength) {
	try {
		if (sideLength.x > 0 && sideLength.y > 0) {
			Brick::sideLength = sideLength;
			changeEntity = true;
			settlePlace();
		}
		else {
			invalid_argument("Side-length cannot be negative.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::setSideLength(const float wid, const float hei) {
	try {
		if (wid > 0 && hei > 0) {
			sideLength = Vector2f(wid, hei);
			changeEntity = true;
			settlePlace();
		}
		else {
			invalid_argument("Side-length cannot be negative.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::setInterval(const Vector2f &interval) {
	try {
		if (interval.x >= 0.0f && interval.y >= 0.0f) {
			Brick::interval = interval;
			settlePlace();
		}
		else {
			invalid_argument("Interval cannot be negative.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::setInterval(const float x, const float y) {
	try {
		if (x >= 0.0f && y >= 0.0f) {
			interval = Vector2f(x, y);
			settlePlace();
		}
		else {
			invalid_argument("Interval cannot be negative.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::setFrameSize(const float frameSize) {
	try {
		if (frameSize >= 0.0f) {
			frame = frameSize;
			changeEntity = true;
			settlePlace();
		}
		else {
			invalid_argument("Frame size cannot be negative.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
}

void Brick::update() {

	if (!bricks.empty()) {
		for (size_t i = 0; i < getBricksSize(); ++i) {
			if (Ball::isBallCollided(getDP(i), sys::DPointf(Vector2f(), bricksArea.getSize()))) {
				bricks.erase(bricks.begin() + i);
				--i;
			}
		}
	}
	else {
		GameState::ready = false;
		GameState::start = false;
		GameState::finishLevel = true;
		std::cout << "Finished level: " << level++ << "!!!" << std::endl;
		reset(level);
		setBrickColor(sf::Color(rng() % 255, rng() % 255, rng() % 255));
	}
}

void Brick::reset(const size_t rowCount, const float wid, const float hei
	, const Vector2f &interval, const float frameSize, const float whiteSpaceY) {

	try {
		if (wid <= 0.0f || hei <= 0.0f
			|| interval.x < 0.0f || interval.y < 0.0f
			|| frameSize < 0.0f || whiteSpaceY < 0.0f) {
			throw invalid_argument("Invaild brick initialization.");
		}
		else {
			sideLength = Vector2f(wid, hei);
			Brick::rowCount = rowCount;
			frame = frameSize;
			Brick::interval = interval;
			amount = static_cast<size_t>((LEVEL_WIDTH - getInterval().x) / (getInterval().x + getSideLength().x + frame * 2));
			whiteSpace.x = (LEVEL_WIDTH - ((Brick::interval.x + sideLength.x + frame * 2) * amount - Brick::interval.x)) / 2;
			whiteSpace.y = whiteSpaceY;
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
	catch (invalid_argument &ex) {
		cout << "Invalid_argument: " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Brick::reset(const size_t rowCount) {
	try {
		Brick::rowCount = rowCount;
		bricks.resize(Brick::rowCount * amount);

		if (getBricksSize() == Brick::rowCount * amount) {
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

const size_t Brick::getBricksSize() {
	return bricks.size();
}

const Vector2f & Brick::getSideLength() {
	return sideLength;
}

const Vector2f & Brick::getInterval() {
	return interval;
}

const float Brick::getFrameSize() {
	return frame;
}

const sys::DPointf Brick::getDP(const size_t number) {
	Vector2f dot1(bricks.at(number)->getGlobalBounds().left, bricks.at(number)->getGlobalBounds().top);
	Vector2f dot2(bricks.at(number)->getGlobalBounds().left + bricks.at(number)->getGlobalBounds().width,
		bricks.at(number)->getGlobalBounds().top + bricks.at(number)->getGlobalBounds().height);
	return sys::DPointf(dot1, dot2);
}

void Brick::settlePlace() {

	const Vector2f initialPos(whiteSpace.x + sideLength.x / 2 + frame, interval.y + frame + sideLength.y / 2);
	Vector2f tempPos = Vector2f(initialPos.x, initialPos.y + whiteSpace.y);
	const float height = rowCount * (sideLength.y + frame * 2 + interval.y) + interval.y + whiteSpace.y;
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
			bricksArea.setSize(Vector2f(LEVEL_WIDTH, height));
			changeEntity = false;
		}

		// ensure that total with the intervals should not be out of screen
		if (whiteSpace.x >= 0.0f) {
			// start placing bricks array
			size_t tempCount = 1;
			for (size_t i = 0; i < bricks.size(); ++i) {
				const FloatRect bounds = bricks.at(i)->getGlobalBounds();
				bricks.at(i)->setPosition(tempPos);
				if (tempCount < amount) {
					tempPos += Vector2f(interval.x + bounds.width, 0);
					++tempCount;
				}
				else {
					tempPos = Vector2f(initialPos.x, tempPos.y + bounds.height + interval.y);
					tempCount = 1;
				}
			}
		}
		else {
			throw domain_error("Intervals are too large to place.");
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	catch (domain_error &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Brick::draw(RenderTarget &target, RenderStates states) const {

	for (size_t i = 0; i < getBricksSize(); ++i) {
		states.texture = bricks.at(i)->getTexture();
		target.draw(*bricks.at(i), states);
	}
}
