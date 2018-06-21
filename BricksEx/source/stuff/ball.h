#pragma once

#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <memory>

namespace sf {
	class RenderTarget;
	class RenderStates;
	class Color;
}

namespace item {
	class Ball :
		public sf::Drawable
		, public sf::Transformable {

	public:
		Ball();
		explicit Ball(const Ball &copy);
		virtual void update(const sys::DPointf &playerDP, const float updateRatio);
		virtual void initializeBall();
		virtual void followPlayer(const sf::Vector2f &pos);
		virtual void ballCollidedObstacle(const size_t number, const size_t blockNumber, const sys::DPointf boundsDP, const sf::Vector2f &speed);
		virtual void ballCollidedObstaclePre(const size_t number, const size_t blockNumber, const sys::DPointf boundsDP, const sf::Vector2f &speed);
		virtual const bool isBallCollidedBrick(const size_t number, const size_t brickNumber, const sys::DPointf boundsDP);
		virtual const bool isBallCollidedBrickPre(const size_t number, const size_t brickNumber, const sys::DPointf boundsDP);
		virtual const bool isBallEnteredObstacleArea(const size_t ballNumber) const;
		virtual const bool isBallEnteredBricksArea(const size_t ballNumber) const;
		virtual void ballDivided(const size_t numbers);

		virtual const float getMainBallRadius() const;
		virtual const sf::Vector2f & getMainBallPosition() const;
		virtual const size_t getBallsAmount() const;
		virtual Ball &operator =(const Ball &copy);
		virtual ~Ball();

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		virtual void ballsCollision(const size_t);

		class BallContainer :
			public sf::Drawable
			, public sf::Transformable {
		public:
			explicit BallContainer(bool &);
			explicit BallContainer(const BallContainer &);
			void move(const sys::DPointf &, bool &, const float);
			void setSpeedX(const float);
			void setSpeedY(const float);
			void setSpeed(const sf::Vector2f &);
			void setPos(const sf::Vector2f &);
			void setPos(const float, const float);
			void setRadius(const float);
			void setColor(const sf::Color &);
			virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

			const bool isMain() const;
			const float getSpeedX() const;
			const float getSpeedY() const;
			const float getRad() const;
			const sf::Vector2f & getPos() const;

			bool left;
			bool right;
			bool bottom;
			bool top;
			bool broke;
			bool CD;
			bool active;
			sf::Clock countTime;

		private:
			void hitByPlayer(const sys::DPointf &);
			void determineUpdate(bool &);
			void resetBall();
			bool main;
			sf::Vector2f ballSpeed;
			sf::Vector2f oriSpeed;
			sf::Clock CDTime;
			sf::CircleShape ball;
		};

		bool multiple;
		bool ballStartC;
		bool mainSettled;
		bool initialized;
		std::vector<std::shared_ptr<BallContainer>> balls;
	};
}
