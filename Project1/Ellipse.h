#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class EllipseShape : public Shape {

public:

	explicit EllipseShape(const Vector2f &);
	void setRadius(const Vector2f &);
	const Vector2f &getRadius() const;
	void setPointCount(size_t);
	virtual unsigned int getPointCount() const;
	virtual Vector2f getPoint(unsigned int) const;

private:

	Vector2f m_radius;
	size_t pointCount = 30;
};