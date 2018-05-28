#pragma once

#include "diagonalPoint.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace item {
	class Block;
	class Ball;
}

class Obstacle : public sf::Drawable {

public:
	Obstacle();
	explicit Obstacle(const Obstacle &copy);
	virtual void reset(const std::vector <sf::Vector2f> &position, const std::vector <sf::Vector2f> &sideLength);
	virtual void update(item::Ball &ball);
	virtual void preUpdate(item::Ball &ball, const float intervalTime);
	virtual void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	virtual void setBlockColor(const size_t number, const sf::Color &all);
	virtual void setAllColor(const std::vector <sf::Color> &color);
	virtual void setAllVerticeColor(const std::vector <sf::Color> &vertice);
	virtual void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	virtual void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	virtual void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	virtual void restart();

	virtual const sf::Vector2f & getSpeed(const size_t number) const;
	virtual const sys::DPointf getDP(const size_t number) const;
	virtual const size_t getBlocksAmount() const;
	Obstacle & operator =(const Obstacle &);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	virtual void blocksCollision(const size_t);

	std::vector <std::shared_ptr<item::Block>> blocks;
};