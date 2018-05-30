#include "block.h"
#include "../definition/define.h"

using namespace std;
using namespace sf;
using namespace item;

Block::Block(const Vector2f & position, const float width, const float height)
	: VertexArray(Quads, 4), position(position), oriPos(position), width(width), height(height) {
	setBlockVertice();
}

Block::Block(const Block & copy)
	: VertexArray(copy.getPrimitiveType(), copy.getVertexCount())
	, position(copy.position)
	, oriPos(copy.oriPos)
	, speed(copy.speed)
	, width(copy.width)
	, height(copy.height) {
	setVerticeColor(copy.getVerticeColor(0), copy.getVerticeColor(1)
		, copy.getVerticeColor(2), copy.getVerticeColor(3));
	setBlockVertice();
}

void Block::setVerticeColor(const Color & color) {
	for (size_t i = 0; i < getVertexCount(); ++i) {
		(*this)[i].color = color;
	}
}

void Block::setVerticeColor(const Color & c1, const Color & c2, const Color & c3, const Color & c4) {
	(*this)[0].color = c1;
	(*this)[1].color = c2;
	(*this)[2].color = c3;
	(*this)[3].color = c4;
}

void Block::setWidth(const float width) {
	if (width > 0) {
		this->width = width;
		setBlockVertice();
	}
	else {
		throw invalid_argument("Invalid width cannot be negetive.");
	}
}

void Block::setHeight(const float height) {
	if (height > 0) {
		this->height = height;
		setBlockVertice();
	}
	else {
		throw invalid_argument("Invalid height cannot be negative.");
	}
}

void Block::resetPosition() {
	position = oriPos;
	setBlockVertice();
}

void Block::setSpeed(const float speedX, const float speedY) {
	speed.x = speedX;
	speed.y = speedY;
}

void Block::setSpeed(const Vector2f & speed) {
	this->speed = speed;
}

// all change direct by using abs() to prevent stuck inside the block
void Block::update() {

	const Vector2f posLT = (*this)[0].position;
	const Vector2f posRB = (*this)[2].position;

	if (posLT.x <= 0.0f) {
		speed.x = abs(speed.x);
	}
	else if (posRB.x >= LEVEL_WIDTH) {
		speed.x = -abs(speed.x);
	}
	if (posLT.y <= 0.0f) {
		speed.y = abs(speed.y);
	}
	else if (posRB.y >= LEVEL_HEIGHT) {
		speed.y = -abs(speed.y);
	}
	moveEntity();
}

void Block::preUpdate(const float intervalTime) {

	const Vector2f posLT = (*this)[0].position;
	const Vector2f posRB = (*this)[2].position;

	if (posLT.x <= 0.0f) {
		speed.x = abs(speed.x);
	}
	else if (posRB.x >= LEVEL_WIDTH) {
		speed.x = -abs(speed.x);
	}
	if (posLT.y <= 0.0f) {
		speed.y = abs(speed.y);
	}
	else if (posRB.y >= LEVEL_HEIGHT) {
		speed.y = -abs(speed.y);
	}
	moveEntity(intervalTime);
}

const sys::DPointf Block::getDP() const {
	return sys::DPointf((*this)[0].position, (*this)[2].position);
}

const sf::Color & item::Block::getVerticeColor(const size_t index) const {
	return (*this)[index].color;
}

const Vector2f Block::getCenterPosition() const {
	return Vector2f(((*this)[0].position.x + (*this)[2].position.x) / 2,
		((*this)[0].position.y + (*this)[2].position.y) / 2);
}

const Vector2f & Block::getCurrentPosition() const {
	return position;
}

const Vector2f & Block::getOriginPosition() const {
	return oriPos;
}

const Vector2f & Block::getSpeed() const {
	return speed;
}

const float Block::getWidth() const {
	return width;
}

const float Block::getHeight() const {
	return height;
}

void Block::setBlockVertice() {

	if (width <= 0 && height <= 0) {
		throw domain_error("Invalid side-length for block.");
	}

	for (size_t i = 0; i < getVertexCount(); ++i) {
		(*this)[i].position = position;
	}

	(*this)[1].position += Vector2f(width, 0.0f);
	(*this)[2].position += Vector2f(width, height);
	(*this)[3].position += Vector2f(0.0f, height);
}

void Block::moveEntity(const float intervalTime) {

	for (size_t i = 0; i < getVertexCount(); ++i) {
		(*this)[i].position += (speed / static_cast<float>(SLICE)) * intervalTime;
	}
	position = (*this)[0].position;// mark new position in [0]
}