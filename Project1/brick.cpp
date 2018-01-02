#include "define.h"
#include "brick.h"
#include <stdexcept>
#include <iostream>

Brick::Brick(const size_t row, const size_t col, const float wid, const float hei){

	try {
		if (row <= 0 || col <= 0 || wid <= 0 || hei <= 0) {
			throw domain_error("Invaild brick initialization.");
		}
		else {
			area.resize(row * col);
			width = wid;
			height = hei;
		}
	}
	catch (domain_error &ex) {

		cout << "Exception: " << ex.what() << endl;
	}
}

void Brick::setArea(const size_t row, const size_t column) {

	if (row > 0 && column > 0) {
		area.resize(row * column);
	}
	else {
		cout << "Invalid area setting." << endl;
	}
}

void Brick::setWidth(const float width){

	if (width > 0) {
		this->width = width;
	}
	else {
		cout << "Invalid width setting." << endl;
	}
}

void Brick::setHeight(const float height){

	if (height > 0) {
		this->height = height;
	}
	else {
		cout << "Invalid height setting." << endl;
	}
}

constexpr float Brick::getWidth() const{
	return width;
}

constexpr float Brick::getHeight() const{
	return height;
}
