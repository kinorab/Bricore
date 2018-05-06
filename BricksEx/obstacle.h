#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "diagonalPoint.h"

namespace item {
	class Block;
}

class Obstacle : public sf::Drawable {

public:
	static std::shared_ptr<Obstacle> getInstance();
	static std::shared_ptr<Obstacle> getPredictInstance();
	static bool resetInstance();
	void reset(const std::vector <sf::Vector2f> &position, const std::vector <sf::Vector2f> &sideLength);
	void update();
	void setBlockColor(const size_t number, const sf::Color &c1, const sf::Color &c2, const sf::Color &c3, const sf::Color &c4);
	void setBlockColor(const size_t number, const sf::Color &all);
	void setAllColor(const std::vector <sf::Color> &color);
	void setAllVerticeColor(const std::vector <sf::Color> &vertice);
	void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
	void setBlockSpeed(const size_t, const sf::Vector2f &speed);
	void setAllSpeed(const std::vector <sf::Vector2f> &speed);
	void setBlocksAreaDP(const sys::DPointf &DP);
	void restart();

	const sf::Vector2f & getBlockSpeed(const size_t number) const;
	const size_t getBlocksAmount() const;
	const sys::DPointf getDP(const size_t number) const;
	const sys::DPointf getBlocksAreaDP() const;

protected:
	Obstacle();

private:
	Obstacle & operator =(const Obstacle &);
	static std::shared_ptr<Obstacle> instance;
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	void blockCollision(const size_t);

	sf::RectangleShape blocksArea;
	std::vector <std::shared_ptr<item::Block>> blocks;
};