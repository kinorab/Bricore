#include "Block.h"
#include <iostream>
#include <stdexcept>

#define PI 3.141592654f

Block::Block(PrimitiveType m_type, const int count, const Vector2f &ini, float len, int incre)
	: type(m_type), vertexCount(count), position(ini), length(len){

	if (incre != NULL) {
		increRate = incre;
	}
	Block::VertexArray array(type, vertexCount);
	setBlockVertice(array, position, length, increRate);
}

Block::Block(PrimitiveType m_type, const int count, const Vector2f &ini, float len)
	: type(m_type), vertexCount(count), position(ini), length(len) {

	Block::VertexArray array(type, vertexCount);
	setBlockVertice(array, position, length, increRate);
}

void Block::setBlockVertice(VertexArray &array, const Vector2f &initial, float length, const int increRate) {

	try {

		if (length > 0) {

			const float outsideAngle = 360.0f / array.getVertexCount();

			for (size_t i = 0; i < array.getVertexCount(); ++i) {

				array[i].position = initial;
			}// end for
			cout << "(" << array[0].position.x << ", " << array[0].position.y << ")" << endl;// print array vertice position

			for (size_t i = 1; i < array.getVertexCount(); ++i) {

				float countAngle = outsideAngle * i;
				float angle = PI - countAngle / 180 * PI;// place array in clockwise

				float lengthX;
				if (countAngle == 0.0f || countAngle == 180.0f) {
					lengthX = 0.0f;
				}// end if
				else {
					lengthX = sin(angle) * length;
				}

				float lengthY;
				if (countAngle == 90.0f || countAngle == 270.0f) {
					lengthY = 0.0f;
				}// end if
				else {
					lengthY = cos(angle) * length;
				}

				if (!(i == 1 || i == 3)) {
					array[i].position += Vector2f(lengthX, lengthY);
					cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				}
				else {
					array[i].position += Vector2f(lengthX * increRate, lengthY);
					cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				}

				for (size_t j = i + 1; j < array.getVertexCount(); ++j) {

					array[j].position = array[i].position;
				}// end inner for
			}// end outer for
		}// end if
		else {

			throw out_of_range("Invalid initial side-length for item.");
		}// end else
	}// end try
	catch (out_of_range &ex) {

		cout << "Exception: " << ex.what() << endl;
	}// end catch
}

void Block::setIncreRate(const int rate) {

	increRate = rate;
	setBlockVertice(array, position, length, increRate);
}

void Block::setLength(float len) {

	length = len;
	setBlockVertice(array, position, length, increRate);
}

void Block::MovePosition(const Vector2f &pos) {

	for (unsigned int i = 0; i < getVertexCount(); ++i) {

		array[i].position += pos;
	}

	position = array[0].position;// mark new position in [0]
}

const PrimitiveType Block::getPrimitiveType()
{
	return type;
}

const int Block::getVertexCount() const{

	return vertexCount;
}

const Vector2f & Block::getPosition() {

	return position;
}

const float Block::getLength(){

	return length;
}

const int Block::getIncreRate(){

	return increRate;
}