#include "wall.h"
#include "ball.h"
#include "component/globular.h"
#include "component/mainBall.h"
#include "component/brick.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"
#include "../gameSys/LVDeploy.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace item;

Wall::Wall()
	: whiteSpace(0.0f, 0.0f)
	, changeEntity(false) {
	reset(static_cast<size_t>(LVDeploy::getBrickD().at(0))
		, LVDeploy::getBrickD().at(1)
		, LVDeploy::getBrickD().at(2)
		, sf::Vector2f(LVDeploy::getBrickD().at(3), LVDeploy::getBrickD().at(4))
		, LVDeploy::getBrickD().at(5)
		, LVDeploy::getBrickD().at(6));
	setBricksColor(LVDeploy::getBrickCD().at(0));
}

void Wall::update(Ball &ball, const float updateRatio) {
	if (bricks.empty()) {
		LVDeploy::finishLevel();
		reset(static_cast<size_t>(LVDeploy::getBrickD().at(0))
			, LVDeploy::getBrickD().at(1)
			, LVDeploy::getBrickD().at(2)
			, sf::Vector2f(LVDeploy::getBrickD().at(3), LVDeploy::getBrickD().at(4))
			, LVDeploy::getBrickD().at(5)
			, LVDeploy::getBrickD().at(6));
		setBricksColor(LVDeploy::getBrickCD().at(0));
		return;
	}
	for (size_t i = 0; i < getBrickAmount(); ++i) {
		for (auto element : ball.enteredWallArea()) {
			if (element->isCollidedWall(bricks.at(i).get())) {
				if (std::dynamic_pointer_cast<MainBall>(element)) {
					ball.ballDivided(10);
				}
				bricks.erase(bricks.begin() + i);
				--i;
				break;
			}
		}
	}
}

void Wall::loadTexture(const std::string & fileName) {
	for (size_t i = 0; i < getBrickAmount(); ++i) {
		bricks.at(i)->loadTexture(fileName);
	}
}

void Wall::setBricksColor(const Color &color) {
	for (size_t i = 0; i < getBrickAmount(); ++i) {
		bricks.at(i)->setBrickColor(color);
	}
}

void Wall::setFramesColor(const Color &color) {
	for (size_t i = 0; i < getBrickAmount(); ++i) {
		bricks.at(i)->setFrameColor(color);
	}
}

void Wall::setBricksSize(const Vector2f & sideLength) {
	if (sideLength.x <= 0 || sideLength.y <= 0) throw std::invalid_argument("Side-length cannot be negative.");
	this->sideLength = sideLength;
	changeEntity = true;
	settlePlace();
}

void Wall::setInterval(const Vector2f &interval) {
	if (interval.x < 0.0f || interval.y < 0.0f) throw std::invalid_argument("Interval cannot be negative.");
	this->interval = interval;
	settlePlace();
}

void Wall::setFrameSize(const float frameSize) {
	if (frameSize < 0.0f) throw std::invalid_argument("Frame size cannot be negative.");
	this->frameSize = frameSize;
	changeEntity = true;
	settlePlace();
}

void Wall::reset(const size_t rowCount, const float wid, const float hei
	, const Vector2f &interval, const float frameSize, const float whiteSpaceY) {

	if (wid <= 0.0f || hei <= 0.0f
		|| interval.x < 0.0f || interval.y < 0.0f
		|| frameSize < 0.0f || whiteSpaceY < 0.0f) {
		throw std::invalid_argument("Invaild brick initialization.");
	}
	sideLength = Vector2f(wid, hei);
	this->rowCount = rowCount;
	this->frameSize = frameSize;
	this->interval = interval;
	amount = static_cast<size_t>((LEVEL_WIDTH - getInterval().x) / (getInterval().x + sideLength.x + this->frameSize * 2));
	whiteSpace.x = (LEVEL_WIDTH - ((this->interval.x + sideLength.x + this->frameSize * 2) * amount - this->interval.x)) / 2;
	whiteSpace.y = whiteSpaceY;
	bricks.resize(this->rowCount * amount);

	if (getBrickAmount() != this->rowCount * amount) {
		throw std::out_of_range("The subscripts are out of range.");
	}
	changeEntity = true;
	settlePlace();
}

void Wall::reset(const size_t rowCount) {
	this->rowCount = rowCount;
	bricks.resize(this->rowCount * amount);
	if (getBrickAmount() != this->rowCount * amount) {
		throw std::out_of_range("The subscripts are out of range.");
	}
	changeEntity = true;
	settlePlace();
}

size_t Wall::getBrickAmount() const {
	return bricks.size();
}

const Vector2f & Wall::getBrickSize(const size_t number) const {
	return bricks.at(number)->getBrickSize();
}

const Vector2f & Wall::getInterval() const {
	return interval;
}

float Wall::getFrameSize(const size_t number) const {
	return bricks.at(number)->getFrameSize();
}

sys::DPointf Wall::getDP(const size_t number) const {
	return bricks.at(number)->getDP();
}

const Color & Wall::getBrickColor(const size_t number) const {
	return bricks.at(number)->getBrickColor();
}

Wall::~Wall() { }

void Wall::settlePlace() {
	const Vector2f initialPos(whiteSpace.x + sideLength.x / 2 + frameSize, interval.y + frameSize + sideLength.y / 2);
	Vector2f tempPos = Vector2f(initialPos.x, initialPos.y + whiteSpace.y);
	const float height = rowCount * (sideLength.y + frameSize * 2 + interval.y) + interval.y + whiteSpace.y;
	if (changeEntity) {
		std::for_each(bricks.begin(), bricks.end(), [this](std::shared_ptr<Brick> &element) {
			element.reset(new Brick(sideLength, frameSize));
			if (frameSize > 0.0f) {
				element->setFrameColor(Color::Black);
			}
		});
		game::wallArea.setSize(Vector2f(LEVEL_WIDTH, height));
		changeEntity = false;
	}
	// ensure that total with the intervals should not be out of screen
	if (whiteSpace.x < 0.0f) throw std::domain_error("Intervals are too large to place.");
	// start placing bricks array
	size_t tempCount = 1;
	std::for_each(bricks.begin(), bricks.end(), [&](const std::shared_ptr<Brick> &element) {
		const FloatRect bounds = element->getGlobalBounds();
		element->setPosition(tempPos);
		if (tempCount < amount) {
			tempPos += Vector2f(interval.x + bounds.width, 0);
			++tempCount;
		}
		else {
			tempPos = Vector2f(initialPos.x, tempPos.y + bounds.height + interval.y);
			tempCount = 1;
		}
	});
}

void Wall::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();
	for (size_t i = 0; i < getBrickAmount(); ++i) {
		target.draw(*bricks.at(i), states);
	}
}
