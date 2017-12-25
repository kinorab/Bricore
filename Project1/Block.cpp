#include "define.h"
#include "block.h"
#include <iostream>
#include <stdexcept>

Block::Block(const enum PrimitiveType type, const int vertexCount, const Vector2f &pos, float wid, float hei)
	: VertexArray(type, vertexCount), position(pos), width(wid), height(hei) {

	setBlockVertice(position, width, height);
}

void Block::setBlockVertice(const Vector2f &position, const float width, const float height) {
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
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Block::setVerticeColor(const Color &color) {

	for (size_t i = 0; i < getVertexCount(); ++i) {

		(*this)[i].color = color;
	}
}

void Block::setVerticeColor(const Color &c1, const Color &c2, const Color &c3, const Color &c4){

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

void Block::MovePosition(const Vector2f &pos) {
	for (size_t i = 0; i < getVertexCount(); ++i) {
		(*this)[i].position += pos;
	}

	position = (*this)[0].position;// mark new position in [0]
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