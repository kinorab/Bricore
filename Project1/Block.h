#pragma once

#include <SFML/Graphics.hpp>

class Block : public sf::VertexArray, sf::Color {
public:

	Block(const enum sf::PrimitiveType type, const size_t vertexCount, const sf::Vector2f &position, float width, float height);

	void setVerticeColor(const sf::Color &);
	void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
	void setWidth(const float width);
	void setHeight(const float height);
	void movePosition(const sf::Vector2f &pos);
	void enable(sf::CircleShape &ball, float &speedX, float &speedY);

	const sf::Vector2f & getPosition() const;
	const float getWidth() const;
	const float getHeight() const;
	//void getStatus();

private:
	void setBlockVertice(const sf::Vector2f &, const float, const float);
	sf::Vector2f position;
	float width;
	float height;
};