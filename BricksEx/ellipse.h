#pragma once

#include <SFML/Graphics.hpp>

class EllipseShape :
	public sf::Shape {

public:

	explicit EllipseShape(const sf::Vector2f &);
	void setRadius(const sf::Vector2f &);
	void setPointCount(size_t);

	const sf::Vector2f &getRadius() const;
	virtual unsigned int getPointCount() const override;
	virtual sf::Vector2f getPoint(unsigned int) const override;

private:

	sf::Vector2f m_radius;
	size_t pointCount = 30;
};