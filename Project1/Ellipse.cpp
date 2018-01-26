#include "ellipse.h"
#include "define.h"
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace sf;


EllipseShape::EllipseShape(const Vector2f &radius = Vector2f(0, 0)) {

	try {
		if (radius.x < 0.0f && radius.y < 0.0f) {
			throw domain_error("Radius of ellipse can't be negative.");
		}

		m_radius = radius;
		update();
	}
	catch (domain_error &ex) {

		cout << "Domain Error: " << ex.what() << endl;
	}
}

void EllipseShape::setRadius(const Vector2f &radius) {

	try {
		if (radius.x < 0.0f && radius.y < 0.0f) {
			throw domain_error("Radius of ellipse can't be negative.");
		}

		m_radius = radius;
		update();
	}
	catch (domain_error &ex) {

		cout << "Domain Error: " << ex.what() << endl;
	}
}

void EllipseShape::setPointCount(size_t count) {

	pointCount = count;
}// end function setPointCount

const Vector2f & EllipseShape::getRadius() const {

	return m_radius;
}// end function getRadius

unsigned int EllipseShape::getPointCount() const {

	return pointCount;
}// end function getPointCount

Vector2f EllipseShape::getPoint(unsigned int index)  const {

	float angle = index * 2 * PI / getPointCount() - PI / 2;
	float x = cos(angle) * m_radius.x;
	float y = sin(angle) * m_radius.y;

	return Vector2f(m_radius.x + x, m_radius.y + y);
}// end function getPoint 