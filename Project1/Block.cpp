#include "define.h"
#include "block.h"
#include <iostream>
#include <stdexcept>

Block::Block(const enum PrimitiveType type, const int vertexCount, const Vector2f & position, float width, float height)
	: VertexArray(type, vertexCount), position(position), width(width), height(height) {

	setBlockVertice(position, width, height);
}

void Block::setBlockVertice(const Vector2f & position, const float width, const float height) {
	try {
		
		if (width > 0 && height > 0) {

			for (size_t i = 0; i < getVertexCount(); ++i) {
				(*this)[i].position = position;
			}

			(*this)[1].position += Vector2f(width, 0.0f);
			(*this)[2].position += Vector2f(width, height);
			(*this)[3].position += Vector2f(0.0f, height);
		}
		else {
			throw out_of_range("Invalid initial side-length for block.");
		}
	}
	catch (out_of_range & ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Block::setVerticeColor(const Color & color) {

	for (size_t i = 0; i < getVertexCount(); ++i) {

		(*this)[i].color = color;
	}
}

void Block::setVerticeColor(const Color & c1, const Color & c2, const Color & c3, const Color & c4){

	(*this)[0].color = c1;
	(*this)[1].color = c2;
	(*this)[2].color = c3;
	(*this)[3].color = c4;
}

void Block::setWidth(const float width) {
	this->width = width;
	setBlockVertice(getPosition(), getWidth(), getHeight());
}

void Block::setHeight(const float height) {
	this->height = height;
	setBlockVertice(getPosition(), getWidth(), getHeight());
}

void Block::MovePosition(const Vector2f & pos) {
	for (size_t i = 0; i < getVertexCount(); ++i) {
		(*this)[i].position += pos;
	}

	position = (*this)[0].position;// mark new position in [0]
}

// all change direct by using abs() to prevent stuck inside the block
void Block::update(CircleShape & ball, float & speedX, float & speedY) {

	FloatRect blockBounds = getBounds();
	FloatRect ballBounds = ball.getGlobalBounds();
	FloatRect leftBlock = FloatRect(Vector2f(blockBounds.left, blockBounds.top + ball.getRadius()), Vector2f(1, blockBounds.height - ball.getRadius() * 2));
	FloatRect rightBlock = FloatRect(Vector2f(blockBounds.left + blockBounds.width - 1, blockBounds.top + ball.getRadius()), Vector2f(1, blockBounds.height - ball.getRadius() * 2));
	FloatRect topBlock = FloatRect(Vector2f(blockBounds.left + ball.getRadius(), blockBounds.top), Vector2f(blockBounds.width - ball.getRadius() * 2, 1));
	FloatRect bottomBlock = FloatRect(Vector2f(blockBounds.left + ball.getRadius(), blockBounds.top + blockBounds.height - 1), Vector2f(blockBounds.width - ball.getRadius() * 2, 1));

	if (ballBounds.intersects(leftBlock)) {
		speedX = -abs(speedX);
	}
	else if (ballBounds.intersects(rightBlock)) {
		speedX = abs(speedX);
	}

	if (ballBounds.intersects(topBlock)) {
		speedY = -abs(speedY);
	}
	else if (ballBounds.intersects(bottomBlock)) {
		speedY = abs(speedY);
	}
	/*static FloatRect bufferBounds = ballBounds;

	if (ballBounds.intersects(blockBounds)) {
	if (bufferBounds.left- blockBounds.left <= 0)  {
	speedX = -abs(speedX);
	}
	else if ((bufferBounds.left + bufferBounds.width) - (blockBounds.left + blockBounds.width) >= 0){
	speedX = abs(speedX);
	}
	else if ((bufferBounds.top + bufferBounds.height) - (blockBounds.top + bufferBounds.height) <= 0) {
	speedY = -abs(speedY);
	}
	else if ((bufferBounds.top + bufferBounds.height) - (blockBounds.top + blockBounds.height) >= 0) {
	speedY = abs(speedY);
	}
	}

	bufferBounds = ballBounds;*/
}

const Vector2f & Block::getPosition() const {
	return position;
}

const float Block::getWidth() const {
	return width;
}

const float Block::getHeight() const {
	return height;
}