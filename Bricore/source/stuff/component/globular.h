#pragma once
#include "../../interact/interactiveObject.h"
#include "../../definition/diagonalPoint.h"
#include <SFML/System/Clock.hpp>

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
		public game::InteractiveObject
		, public std::enable_shared_from_this<Globular> {
	public:
		virtual bool isCollidedObstacle(const Block * block) = 0;
		virtual bool isCollidedWall(const Brick * brick) = 0;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		void move(const sys::DPointf &DP, const float playerSpeed, const float updateRatio);
		void setSpeedX(const float speedX);
		void setSpeedY(const float speedY);
		void setSpeed(const sf::Vector2f &speed);
		void setPosition(const sf::Vector2f &pos);
		void setPosition(const float posX, const float posY);
		void setRadius(const float radius);
		void setColor(const sf::Color &color);
		void restartClock();
		bool isEnteredObstacleArea() const;
		bool isEnteredWallArea() const;

		bool isBroke() const;
		// include outlineThickness
		float getRadius() const;
		const sf::Vector2f & getSpeed() const;
		const sf::Vector2f & getPosition() const;
		sf::Vector2f getPreviousPos() const;

	protected:
		Globular();
		virtual void determineHitDirect() = 0;
		void setActive(const bool active);
		struct Side {
			void reset();
			bool bLeft;
			bool bRight;
			bool bBottom;
			bool bTop;
		} hitside;
		bool bBroke;
		bool bCD;
		sf::Vector2f ballSpeed;
		sf::Vector2f oriSpeed;
		sf::Clock CDTime;
		sf::Clock countTime;

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void hitByPlayer(const sys::DPointf &DP, const float playerSpeed, const bool continuousCollision);
		void resetBall();

		bool bActive;
		std::shared_ptr<sf::CircleShape> ball;
	};
}
