#pragma once

#include "block.h"
#include <vector>

class Obstacle : public Block {

public:

	Obstacle(const size_t number, const std::vector<sf::Vector2f> &position, const std::vector<sf::Vector2f> &sideLength);
	void enable(sf::CircleShape &ball, float &ballSpeedX, float &ballSpeedY);
	void blockCollision(std::vector <Block*> blocks);
	void setColor(const size_t, const sf::Color, const sf::Color, const sf::Color, const sf::Color);
	
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	std::vector <Block*> blocks;
};
