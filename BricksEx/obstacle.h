#pragma once

#include "block.h"
#include <memory>
#include <vector>

class Obstacle : public sf::Drawable {

public:
	Obstacle();
	static void reset(const std::vector <sf::Vector2f> &position, const std::vector <sf::Vector2f> &sideLength);
	static void update();
	static void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	static void setBlockColor(const size_t number, const sf::Color &all);
	static void setAllColor(const std::vector <sf::Color> &color);
	static void setAllVerticeColor(const std::vector <sf::Color> &vertice);
	static void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	static void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	static void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	static void setBlocksAreaDP(const sys::DPointf &DP);
	static void restart();

	static const sf::Vector2f & getBlockSpeed(const size_t number);
	static const size_t getBlocksAmount();
	static const sys::DPointf getDP(const size_t number);
	static const sys::DPointf getBlocksAreaDP();

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	static void blockCollision(const size_t);

	static sf::RectangleShape blocksArea;
	static std::vector <std::unique_ptr<item::Block>> blocks;
};