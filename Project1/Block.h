#pragma once

#include <SFML/Graphics.hpp>

class Block : public sf::VertexArray{
public:

	Block(const sf::Vector2f &position, float width, float height);
	Block(std::vector<Block*> blocks, const size_t number, const std::vector<sf::Vector2f> &position, const std::vector<sf::Vector2f> &sideLength);
	void setVerticeColor(const sf::Color &);
	void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
	void setWidth(const float width);
	void setHeight(const float height);
	void resetPosition();
	void setSpeed(const float ballSpeedX, const float ballSpeedY = 0.0f);
	void setSpeed(const sf::Vector2f &speed);
	void enable(sf::CircleShape &ball, float &ballSpeedX, float &ballSpeedY);

	const sf::Vector2f & getCurrentPosition() const;
	const sf::Vector2f & getOriginPosition() const;
	const sf::Vector2f & getSpeed() const;
	const float getWidth() const;
	const float getHeight() const;

private:
	void setBlockVertice(const sf::Vector2f &, const float, const float);
	void move();
	void moveEntity(const sf::Vector2f &);

	sf::Vector2f position;
	sf::Vector2f oriPos;
	sf::Vector2f speed;
	float width;
	float height;
};