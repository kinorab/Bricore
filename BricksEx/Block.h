#pragma once

#include <SFML/Graphics.hpp>
#include "diagonalPoint.h"

namespace item {
	class Block : public sf::VertexArray {

	public:
		Block(const sf::Vector2f &position, const float width, const float height);
		void setVerticeColor(const sf::Color &);
		void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
		void setWidth(const float width);
		void setHeight(const float height);
		void resetPosition();
		void setSpeed(const float speedX, const float speedY = 0.0f);
		void setSpeed(const sf::Vector2f &speed);
		void update();

		const sys::DPointf getDP() const;
		const sf::Vector2f & getCurrentPosition() const;
		const sf::Vector2f & getOriginPosition() const;
		const sf::Vector2f & getSpeed() const;
		const float getWidth() const;
		const float getHeight() const;

	protected:
		Block();

	private:
		void setBlockVertice();
		void moveEntity();

		sf::Vector2f position;
		sf::Vector2f oriPos;
		sf::Vector2f speed;
		float width;
		float height;
	};
}