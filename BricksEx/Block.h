#pragma once

#include "diagonalPoint.h"
#include <SFML/Graphics.hpp>

namespace item {
	class Block : public sf::VertexArray {

	public:
		explicit Block(const sf::Vector2f &position, const float width, const float height);
		explicit Block(const Block &copy);
		void setVerticeColor(const sf::Color &);
		void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
		void setWidth(const float width);
		void setHeight(const float height);
		void resetPosition();
		void setSpeed(const float speedX, const float speedY = 0.0f);
		void setSpeed(const sf::Vector2f &speed);
		void update();
		void preUpdate(const float intervalTime);

		const sys::DPointf getDP() const;
		const sf::Color & getVerticeColor(const size_t index) const;
		const sf::Vector2f getCenterPosition() const;
		const sf::Vector2f & getCurrentPosition() const;
		const sf::Vector2f & getOriginPosition() const;
		const sf::Vector2f & getSpeed() const;
		const float getWidth() const;
		const float getHeight() const;

	private:
		void setBlockVertice();
		void moveEntity(const float = 1.f);

		sf::Vector2f position;
		const sf::Vector2f oriPos;
		sf::Vector2f speed;
		float width;
		float height;
	};
}