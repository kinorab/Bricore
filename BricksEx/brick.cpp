#include "brick.h"
#include "ball.h"
#include "define.h"
#include "LVDeploy.h"
#include <stdexcept>

using namespace std;
using namespace sf;
using namespace item;

Brick::Brick()
	: whiteSpace(0.0f, 0.0f)
	, changeEntity(false)
	, frameColor(Color::Black) {
	reset(static_cast<size_t>(LVDeploy::getBrickD().at(0))
		, LVDeploy::getBrickD().at(1)
		, LVDeploy::getBrickD().at(2)
		, sf::Vector2f(LVDeploy::getBrickD().at(3), LVDeploy::getBrickD().at(4))
		, LVDeploy::getBrickD().at(5)
		, LVDeploy::getBrickD().at(6));
	setBrickColor(LVDeploy::getBrickCD().at(0));
}

Brick::Brick(const Brick & copy) {
	bricks.clear();
	std::for_each(copy.bricks.begin(), copy.bricks.end()
		, [&](const std::shared_ptr<RectangleShape> element) {
		bricks.push_back(std::make_shared<RectangleShape>(*element));
	});
	setBrickColor(copy.bricksColor);
	setFrameColor(copy.frameColor);
}

void Brick::update(Ball &ball) {
	if (!bricks.empty()) {
		for (size_t ballN = 0; ballN < ball.getBallsAmount(); ++ballN) {
			if (ball.isBallEnteredBricksArea(ballN)) {
				for (size_t brickN = 0; brickN < getBricksSize(); ++brickN) {
					if (ball.isBallCollidedBrick(ballN, brickN, getDP(brickN))) {
						bricks.erase(bricks.begin() + brickN);
						--brickN;
					}
				}
			}
		}
	}
	else {
		LVDeploy::finishLevel();
		reset(static_cast<size_t>(LVDeploy::getBrickD().at(0))
			, LVDeploy::getBrickD().at(1)
			, LVDeploy::getBrickD().at(2)
			, sf::Vector2f(LVDeploy::getBrickD().at(3), LVDeploy::getBrickD().at(4))
			, LVDeploy::getBrickD().at(5)
			, LVDeploy::getBrickD().at(6));
		setBrickColor(LVDeploy::getBrickCD().at(0));
	}
}

void Brick::preUpdate(Ball & ball, const float intervalTime) {
	if (!bricks.empty()) {
		for (size_t ballN = 0; ballN < ball.getBallsAmount(); ++ballN) {
			if (ball.isBallEnteredBricksArea(ballN)) {
				for (size_t brickN = 0; brickN < getBricksSize(); ++brickN) {
					if (ball.isBallCollidedBrickPre(ballN, brickN, getDP(brickN))) {
						bricks.erase(bricks.begin() + brickN);
						--brickN;
					}
				}
			}
		}
	}
}

void Brick::loadImage(const string fileName) {
	try {
		levelImage.emplace(fileName, new Texture());
		levelImage.at(fileName)->loadFromFile(fileName);
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Brick::loadImage(): " << ex.what() << endl;
	}
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
		cout << "Domain_error in Brick::deleteImage(): " << ex.what() << endl;
	}
}

void Brick::displayImage(const string fileName) {
	try {
		for (size_t i = 0; i < getBricksSize(); ++i) {
			bricks.at(i)->setTexture(levelImage.at(fileName));
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Brick::displayImage(): " << ex.what() << endl;
	}
}

void Brick::setBrickColor(const Color &color) {
	try {
		bricksColor = color;
		for (size_t i = 0; i < getBricksSize(); ++i) {
			bricks.at(i)->setFillColor(color);
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Brick::setBrickColor(): " << ex.what() << endl;
	}
}

void Brick::setFrameColor(const Color &color) {
	try {
		if (frame > 0.0f) {
			frameColor = color;
			for (size_t i = 0; i < getBricksSize(); ++i) {
				bricks.at(i)->setOutlineColor(color);
			}
		}
		else {
			invalid_argument("Brick frames do not exist.");
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument in Brick::setFrameColor(): " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Brick::setFrameColor(): " << ex.what() << endl;
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
		cout << "Invalid_argument in Brick::setSideLength(): " << ex.what() << endl;
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
		cout << "Invalid_argument in Brick::setSideLength(): " << ex.what() << endl;
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
		cout << "Invalid_argument in Brick::setInterval(): " << ex.what() << endl;
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
		cout << "Invalid_argument in Brick::setInterval(): " << ex.what() << endl;
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
		cout << "Invalid_argument in Brick::setFrameSize(): " << ex.what() << endl;
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
			this->rowCount = rowCount;
			frame = frameSize;
			this->interval = interval;
			amount = static_cast<size_t>((LEVEL_WIDTH - getInterval().x) / (getInterval().x + getSideLength().x + frame * 2));
			whiteSpace.x = (LEVEL_WIDTH - ((this->interval.x + sideLength.x + frame * 2) * amount - this->interval.x)) / 2;
			whiteSpace.y = whiteSpaceY;
			bricks.resize(this->rowCount * amount);

			if (getBricksSize() == this->rowCount * amount) {
				changeEntity = true;
				settlePlace();
			}
			else {
				throw out_of_range("The subscripts are out of range.");
			}
		}
	}
	catch (invalid_argument &ex) {
		cout << "Invalid_argument in Brick::reset(): " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Brick::reset(): " << ex.what() << endl;
	}
}

void Brick::reset(const size_t rowCount) {
	try {
		this->rowCount = rowCount;
		bricks.resize(this->rowCount * amount);

		if (getBricksSize() == this->rowCount * amount) {
			changeEntity = true;
			settlePlace();
		}
		else {
			throw out_of_range("The subscripts are out of range.");
		}
	}
	catch (out_of_range &ex) {
		cout << "Out_of_range in Brick::reset(): " << ex.what() << endl;
	}
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

const sys::DPointf Brick::getDP(const size_t number) const {
	return sys::DPointf(bricks.at(number)->getGlobalBounds());
}

const sf::Color Brick::getBricksColor() const {
	return bricksColor;
}

Brick::~Brick() { }

Brick & Brick::operator=(const Brick &right) {
	bricks.clear();
	std::for_each(right.bricks.begin(), right.bricks.end()
		, [&](const std::shared_ptr<RectangleShape> element) {
		bricks.push_back(std::make_shared<RectangleShape>(*element));
	});
	setBrickColor(right.bricksColor);
	setFrameColor(right.frameColor);
	return *this;
}

void Brick::settlePlace() {

	const Vector2f initialPos(whiteSpace.x + sideLength.x / 2 + frame, interval.y + frame + sideLength.y / 2);
	Vector2f tempPos = Vector2f(initialPos.x, initialPos.y + whiteSpace.y);
	const float height = rowCount * (sideLength.y + frame * 2 + interval.y) + interval.y + whiteSpace.y;
	try {
		if (changeEntity == true) {
			for (size_t i = 0; i < bricks.size(); ++i) {
				bricks.at(i) = shared_ptr<RectangleShape>(new RectangleShape(Vector2f(sideLength.x, sideLength.y)));
				if (frame > 0.0f) {
					bricks.at(i)->setOutlineThickness(frame);
					bricks.at(i)->setOutlineColor(Color::Black);
				}
				// center origin position in every brick
				bricks.at(i)->setOrigin(Vector2f(bricks.at(i)->getSize().x / 2, bricks.at(i)->getSize().y / 2));
			}
			GameState::bricksArea.setSize(Vector2f(LEVEL_WIDTH, height));
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
		cout << "Out_of_range in Brick::settlePlace(): " << ex.what() << endl;
	}
	catch (domain_error &ex) {
		cout << "Domain_error in Brick::settlePlace(): " << ex.what() << endl;
	}
}

void Brick::draw(RenderTarget &target, RenderStates states) const {
	for (size_t i = 0; i < getBricksSize(); ++i) {
		states.texture = bricks.at(i)->getTexture();
		target.draw(*bricks.at(i), states);
	}
}
