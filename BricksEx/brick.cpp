#include "brick.h"
#include "ball.h"
#include "define.h"
#include "levelDeploy.h"
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
std::mutex Brick::mutex;
std::shared_ptr<Brick> Brick::instance = nullptr;

Brick::Brick() { 
	LVDeploy::changeBrickD();
}

void Brick::loadImage(const string fileName) {
	levelImage.emplace(fileName, new Texture());
	levelImage.at(fileName)->loadFromFile(fileName);
}

void Brick::deleteImage(const string fileName) {
	const auto image = levelImage.find(fileName);
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

std::shared_ptr<Brick> item::Brick::getInstance() {
	std::shared_ptr<Brick> brickPtr = std::atomic_load_explicit(&instance, std::memory_order_acquire);
	if (!brickPtr) {
		// prevent multithread get instance
		std::lock_guard<std::mutex> lock(mutex);
		brickPtr = std::atomic_load_explicit(&instance, std::memory_order_relaxed);
		if (!brickPtr) {
			brickPtr = std::shared_ptr<Brick>(new Brick());
			std::atomic_store_explicit(&instance, brickPtr, std::memory_order_release);
		}
	}
	return brickPtr;
}

void Brick::update() {

	if (!bricks.empty()) {
		for (size_t i = 0; i < Ball::getBallsAmount(); ++i) {
			if (Ball::isBallEnteredBricksArea(i)){
				for (size_t j = 0; j < getBricksSize(); ++j) {
					if (Ball::isBallCollided(i, j)) {
						bricks.erase(bricks.begin() + j);
						--j;
					}
				}
			}
		}
	}
	else {
		LVDeploy::finishLevel();
		LVDeploy::changeBrickD();
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
	const Vector2f LT(bricks.at(number)->getGlobalBounds().left, bricks.at(number)->getGlobalBounds().top);
	const Vector2f RB(LT.x + bricks.at(number)->getGlobalBounds().width, LT.y + bricks.at(number)->getGlobalBounds().height);
	return sys::DPointf(LT, RB);
}

const sys::DPointf Brick::getBrickAreaDP() {
	const FloatRect bounds = bricksArea.getGlobalBounds();
	const Vector2f LT(bounds.left, bounds.top);
	const Vector2f RB(bounds.left + bounds.width, bounds.top + bounds.height);
	return sys::DPointf(LT, RB);
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
