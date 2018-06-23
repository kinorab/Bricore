#pragma once
#include "../../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include <functional>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class CircleShape;
	class Color;
}

namespace item {
	class Block;
	class Brick;

	class Globular :
		public sf::Drawable
		, public sf::Transformable {
	public:
		virtual void move(const sys::DPointf &DP, const float playerSpeed, const float updateRatio);
		virtual void setSpeedX(const float speedX);
		virtual void setSpeedY(const float speedY);
		virtual void setSpeed(const sf::Vector2f &speed);
		virtual void setPosition(const sf::Vector2f &pos);
		virtual void setPosition(const float posX, const float posY);
		virtual void setRadius(const float radius);
		virtual void setColor(const sf::Color &color);
		virtual void restartClock();
		virtual bool isCollidedObstacle(const Block * block) = 0;
		virtual bool isCollidedWall(const Brick * brick) = 0;
		virtual bool isEnteredObstacleArea() const;
		virtual bool isEnteredWallArea() const;

		virtual bool isBroke() const;
		// include outlineThickness
		virtual float getRadius() const;
		virtual const sf::Vector2f & getSpeed() const;
		virtual const sf::Vector2f & getPosition() const;
		virtual sf::Vector2f getPreviousPos() const;

	protected:
		Globular();
		virtual void determineUpdate() = 0;
		virtual void setActive(const bool active);
		bool broke;
		bool left;
		bool right;
		bool bottom;
		bool top;
		bool CD;
		sf::Vector2f ballSpeed;
		sf::Vector2f oriSpeed;
		sf::Clock CDTime;
		sf::Clock countTime;

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void hitByPlayer(const sys::DPointf &, const float, const bool);
		virtual void resetBall();

		bool active;
		std::shared_ptr<sf::CircleShape> ball;
	};
}
