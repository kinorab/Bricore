#include "common.h"
#include "block.h"
#include <iostream>
#include <stdexcept>

Block::Block(const PrimitiveType type, const int vertexCount, const Vector2f &position, float width, float height)
	: VertexArray(type, vertexCount), position(position), width(width), height(height) {
	setBlockVertice(position, width, height);
}

void Block::setBlockVertice(const Vector2f &position, const float width, const float height) {
	try {
		cout << VertexArray::getVertexCount();
		if (width > 0 && height > 0) {
			for (size_t i = 0; i < 4; i += 1) {
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
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}

}

void Block::setWidth(const float width) {
	this->width = width;
	setBlockVertice(position, width, height);
}

void Block::setHeight(const float height) {
	this->height = height;
	setBlockVertice(position, width, height);
}

void Block::MovePosition(const Vector2f &pos) {
	for (unsigned int i = 0; i < getVertexCount(); ++i) {
		(*this)[i].position += pos;
	}

	position = (*this)[0].position;// mark new position in [0]
}

const Vector2f & Block::getPosition() const {
	return position;
}

float Block::getWidth() const {
	return width;
}

float Block::getHeight() const {
	return height;
}