#pragma once

#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>
#include <vector>

namespace item {
	class Block;
}

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Color;
}
class Ball;

class Obstacle :
	public sf::Drawable
	, public sf::Transformable {

public:
	Obstacle();
	virtual void update(Ball &ball, const float updateRatio);
	virtual void reset(const std::vector <sf::Vector2f> &position, const std::vector <sf::Vector2f> &sideLength);
	virtual void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	virtual void setBlockColor(const size_t number, const sf::Color &all);
	virtual void setAllColor(const std::vector <sf::Color> &color);
	virtual void setAllVerticeColor(const std::vector <sf::Color> &vertice);
	virtual void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	virtual void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	virtual void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	virtual void resetPosition();
	virtual ~Obstacle();

	virtual size_t getBlocksAmount() const;
	virtual sys::DPointf getDP(const size_t number) const;
	virtual const sf::Vector2f & getSpeed(const size_t number) const;

protected:
	virtual void blocksCollision(const size_t);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	std::vector <std::shared_ptr<item::Block>> blocks;
};