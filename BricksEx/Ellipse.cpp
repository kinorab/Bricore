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
		cout << "Domain_error in EllipseShape constructor: " << ex.what() << endl;
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
		cout << "Domain_error in EllipseShape::setRadius(): " << ex.what() << endl;
	}
}

void EllipseShape::setPointCount(size_t count) {
	pointCount = count;
}

const Vector2f & EllipseShape::getRadius() const {
	return m_radius;
}

size_t EllipseShape::getPointCount() const {
	return pointCount;
}

Vector2f EllipseShape::getPoint(size_t index)  const {
	float angle = index * 2 * PI / getPointCount() - PI / 2;
	float x = cos(angle) * m_radius.x;
	float y = sin(angle) * m_radius.y;
	return Vector2f(m_radius.x + x, m_radius.y + y);
}