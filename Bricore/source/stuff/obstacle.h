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
	void update(Ball &ball, const float updateRatio);
	void reset(const std::vector <sf::Vector2f> &position, const std::vector <sf::Vector2f> &sideLength);
	void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	void setBlockColor(const size_t number, const sf::Color &all);
	void setAllColor(const std::vector <sf::Color> &color);
	void setAllVerticeColor(const std::vector <sf::Color> &vertice);
	void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	void resetPosition();
	virtual ~Obstacle();

	size_t getBlocksAmount() const;
	sys::DPointf getDP(const size_t number) const;
	const sf::Vector2f & getSpeed(const size_t number) const;

protected:
	void blocksCollision(const size_t);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	std::vector <std::shared_ptr<item::Block>> blocks;
};