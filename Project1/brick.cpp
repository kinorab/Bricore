#include "define.h"
#include "brick.h"
#include <stdexcept>
#include <iostream>

// user set the brick array manually
Brick::Brick(const size_t row, const size_t col, const float wid, const float hei, Window *window, const Vector2f &interval){

	try {
		if (row <= 0 || col <= 0 || wid <= 0 || hei <= 0 || interval.x < 0.0f || interval.y < 0.0f) {
			throw domain_error("Invaild brick initialization.");
		}
		else if (col * wid + interval.x * (col + 1) > window->getSize().x
			  || row * hei + interval.y * (row + 1) > window->getSize().y) {
			throw domain_error("Invaild brick initialization.");
		}
		else {
			area.resize(row * col);
			amount = col;
			sideLength = Vector2f(wid, hei);
			this->interval = interval;

			if (getAreaSize() == row * amount) {
				settlePlace(getArea(), window, getInterval());
			}
			else {
				throw out_of_range("The subscripts are out of range.");
			}
		}
	}
	catch (domain_error &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

// auto full up the window
Brick::Brick(const size_t rowAmount, const float wid, const float hei, Window * window, const Vector2f &interval){

	try {
		if (rowAmount <= 0 || wid <= 0 || hei <= 0 || interval.x < 0.0f || interval.y < 0.0f) {
			throw domain_error("Invaild brick initialization.");
		}
		else {
			sideLength = Vector2f(wid, hei);
			this->interval = interval;
			amount = static_cast<size_t>(window->getSize().x / (getInterval().x + sideLength.x));
			area.resize(rowAmount * amount);

			if (getAreaSize() == rowAmount * amount) {
				settlePlace(getArea(), window, getInterval());
			}
			else {
				throw out_of_range("The subscripts are out of range.");
			}
		}
	}
	catch (domain_error &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

void Brick::loadImage(Texture *image){
	for (size_t i = 0; i < getAreaSize(); ++i) {
		area.at(i).setTexture(image);
	}
}

void Brick::fillEntityColor(const Color &color){
	for (size_t i = 0; i < getAreaSize(); ++i) {
		area.at(i).setFillColor(color);
	}
}

void Brick::setRowAmount(const size_t row, Window *window) {

	if (row > 0) {
		area.resize(row * amount);
		changeEntity = true;
		settlePlace(getArea(), window, getInterval());
	}
	else {
		cout << "Invalid area setting." << endl;
	}
}

void Brick::setInterval(const Vector2f &interval, Window *window) {

	if (interval.x >= 0.0f && interval.y >= 0.0f) {
		this->interval = interval;
		settlePlace(getArea(), window, getInterval());
	}
	else {
		cout << "Invalid interval setting." << endl;
	}
}

void Brick::setInterval(const float x, const float y, Window *window) {

	if (x >= 0.0f && y >= 0.0f) {
		interval = Vector2f(x, y);
		settlePlace(getArea(), window, getInterval());
	}
	else {
		cout << "Invalid interval setting." << endl;
	}
}

void Brick::setSideLength(const Vector2f & sideLength, Window * window){

	if (sideLength.x > 0 && sideLength.y > 0) {
		this->sideLength = sideLength;
		changeEntity = true;
		settlePlace(getArea(), window, getInterval());
	}
	else {
		cout << "Invalid side-length setting." << endl;
	}
}

void Brick::setSideLength(const float wid, const float hei, Window *window){

	if (wid > 0 && hei > 0) {
		sideLength = Vector2f(wid, hei);
		changeEntity = true;
		settlePlace(getArea(), window, getInterval());
	}
	else {
		cout << "Invalid side-length setting." << endl;
	}
}

const size_t Brick::getAreaSize() const {
	return getArea().size();
}

const Vector2f & Brick::getSideLength() const{
	return sideLength;
}

const Vector2f & Brick::getInterval() const{
	return interval;
}

void Brick::settlePlace(vector<RectangleShape> area, Window *window, const Vector2f &interval){

	try {
		if (changeEntity == true) {
			for (size_t i = 0; i < area.size(); ++i) {
				area.at(i).setSize(Vector2f(sideLength.x, sideLength.y));
				// center origin position in every brick
				area.at(i).setOrigin(Vector2f(area.at(i).getSize().x / 2, area.at(i).getSize().y / 2));
			}
			changeEntity = false;
		}

		// ensure that total which plus the intervals should not out of screen
		static const float whiteSpace = (window->getSize().x - ((interval.x + sideLength.x) * amount + interval.x)) / 2;
		if (whiteSpace >= 0.0f) {
			// start placing area array
			for (size_t i = 0; i < area.size(); ++i) {

				// if window's size().x cannot be filled with full screen, remain the white space of bound
				static const Vector2f initialPos(whiteSpace + interval.x + sideLength.x / 2, interval.y + sideLength.y / 2);
				static Vector2f tempPos = Vector2f(initialPos.x, initialPos.y);
				static size_t tempCount = 0;

				if (tempCount < amount) {
					tempPos += Vector2f(sideLength.x + interval.x, 0);
					++tempCount;
				}
				else {
					tempPos = Vector2f(initialPos.x, tempPos.y + initialPos.y);
					tempCount = 0;
				}
				area.at(i).setPosition(tempPos);
			}
		}
		else {
			cout << "Intervals are too long to place." << endl;
		}
	}
	catch (out_of_range &ex) {
		cout << "Exception: " << ex.what() << endl;
	}
}

const vector<RectangleShape> Brick::getArea() const{
	return area;
}