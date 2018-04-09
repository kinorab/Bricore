#pragma once

#include "block.h"
#include <memory>
#include <vector>

class Obstacle : public sf::Drawable {

public:
	Obstacle(const size_t number, const std::vector <sf::Vector2f> &position, const std::vector<sf::Vector2f> &sideLength);
	static void update();
	static void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	static void setBlockColor(const size_t number, const sf::Color &all);
	static void setAllColor(const std::vector <sf::Color> &color);
	static void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	static void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	static void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	static void reset();

	static const sf::Vector2f & getBlockSpeed(const size_t number);
	static const size_t getBlocksAmount();

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	static void blockCollision(const size_t);

	static std::vector <std::unique_ptr<item::Block>> blocks;
};