#pragma once

#include "block.h"
#include <vector>

namespace item {
	class Obstacle :
		public item::Block {

	public:

		Obstacle(const size_t number, const std::vector <sf::Vector2f> &position, const std::vector<sf::Vector2f> &sideLength);
		void enable(sf::CircleShape &ball, float &ballSpeedX, float &ballSpeedY);
		void setBlockColor(const size_t, const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
		void setBlockColor(const size_t, const sf::Color &);
		void setAllColor(const std::vector <sf::Color> &color);
		void setBlockSpeed(const size_t, const float speedX, const float speedY = 0.0f);
		void setBlockSpeed(const size_t, const sf::Vector2f &speed);
		void setAllSpeed(const std::vector <sf::Vector2f> &speed);
		void reset();

		const size_t getBlocksAmount() const;

	private:
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		void blockCollision(const size_t);
		void move(const size_t);

		std::vector <item::Block*> blocks;
	};
}
