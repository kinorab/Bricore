#pragma once

#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf {
	class Color;
}

namespace item {
	class Block : public sf::VertexArray {

	public:
		explicit Block(const sf::Vector2f &position, const float width, const float height);
		explicit Block(const Block &copy);
		void update(const float intervalRate);
		void setVerticeColor(const sf::Color &);
		void setVerticeColor(const sf::Color &, const sf::Color &, const sf::Color &, const sf::Color &);
		void setWidth(const float width);
		void setHeight(const float height);
		void resetPosition();
		void setSpeed(const float speedX, const float speedY = 0.0f);
		void setSpeed(const sf::Vector2f &speed);

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
		void moveEntity(const float);

		sf::Vector2f position;
		const sf::Vector2f oriPos;
		sf::Vector2f speed;
		float width;
		float height;
	};
}