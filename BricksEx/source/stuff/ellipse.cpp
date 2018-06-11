#include "ellipse.h"
#include "../definition/gameState.h"
#include "../definition/utility.h"

using namespace std;
using namespace sf;

EllipseShape::EllipseShape(const Vector2f &radius = Vector2f(0, 0)) {
	setRadius(radius);
}

void EllipseShape::setRadius(const Vector2f &radius) {
	if (radius.x < 0.0f && radius.y < 0.0f) {
		throw domain_error("Radius of ellipse can't be negative.");
	}

	m_radius = radius;
	update();
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