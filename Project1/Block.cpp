#include "Block.h"
#include <iostream>
#include <stdexcept>

#define PI 3.141592654f

Block::Block(enum PrimitiveType, const int count, const Vector2f &ini, float len, int incre)
	: vertexCount(count), position(ini), length(len){

	if (incre != NULL) {
		increRate = incre;
	}
	setBlockVertice(*this, vertexCount, position, length, increRate);
}

void Block::setBlockVertice(VertexArray &array, const int vertexCount, const Vector2f &initial, float length, const int increRate) {

	try {

		if (length > 0) {

			const float outsideAngle = 360.0f / vertexCount;


			for (size_t i = 0; i < vertexCount; ++i) {

				array[i].position = initial;
			}// end for
			cout << "(" << array[0].position.x << ", " << array[0].position.y << ")" << endl;// print array vertice position

			for (size_t i = 1; i < vertexCount; ++i) {

				float countAngle = outsideAngle * i;
				float angle = PI - countAngle / 180 * PI;// place array in clockwise

				float lengthX = sin(angle) * length;
				if (countAngle == 0.0f || countAngle == 180.0f) {
					lengthX = 0.0f;
				}// end if

				float lengthY = cos(angle) * length;
				if (countAngle == 90.0f || countAngle == 270.0f) {
					lengthY = 0.0f;
				}// end if

				if (!(i == 1 || i == 3)) {
					array[i].position += Vector2f(lengthX, lengthY);
					cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				}
				else {
					array[i].position += Vector2f(lengthX * increRate, lengthY);
					cout << "(" << array[i].position.x << ", " << array[i].position.y << ")" << endl;
				}

				for (size_t j = i + 1; j < vertexCount; ++j) {

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
	setBlockVertice(array, vertexCount, position, length, increRate);
}

void Block::setLength(float len) {

	length = len;
	setBlockVertice(array, vertexCount, position, length, increRate);
}

void Block::MovePosition(const Vector2f &pos) {

	for (unsigned int i = 0; i < vertexCount; ++i) {

		array[i].position += pos;
	}

	position = array[0].position;// mark new position in [0]
}

const int Block::getvertexCount() {

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

