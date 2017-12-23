#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdexcept>
#define PI 3.141592654f

using namespace sf;
using namespace std;

class EllipseShape : public Shape {

public:

	explicit EllipseShape(const Vector2f &radius = Vector2f(0, 0)) {

		if (radius.x > 0 && radius.y > 0) {
			m_radius = radius;
			update();
		}// end if
		else {

			throw out_of_range("The Ellipse has a wrong initialization.");
		}// end else
	}// end EllipseShape constructor

	void setRadius(const Vector2f &radius) {

		if (radius.x > 0 && radius.y > 0) {
			m_radius = radius;
			update();
		}// end if
		else {

			throw out_of_range("The Ellipse has a wrong initialization.");
		}// end else
	}// end function setRadius

	const Vector2f &getRadius() const{

		return m_radius;
	}// end function getRadius

	void setPointCount(size_t count) {

		pointCount = count;
	}// end function setPointCount

	virtual unsigned int getPointCount()  const {

		return pointCount;
	}// end function getPointCount

	virtual Vector2f getPoint(unsigned int index)  const {
	
		float angle = index * 2 * PI / getPointCount() - PI / 2;
		float x = cos(angle) * m_radius.x;
		float y = sin(angle) * m_radius.y;

		return Vector2f(m_radius.x + x, m_radius.y + y);
	}// end function getPoint 

private:

	Vector2f m_radius;
	size_t pointCount = 30;
};