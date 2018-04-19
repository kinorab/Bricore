#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <mutex>
#include "diagonalPoint.h"

namespace item {

	class Ball : public sf::Drawable {

	public:
		static std::shared_ptr<Ball> getInstance();
		static void update(const sys::DPointf &playerDP);
		static void initializeBall();
		static void followPlayer(const sf::Vector2f &playerTopCenterPos);
		static void ballCollided(const size_t number, const size_t blockNumber);
		static const bool isBallCollided(const size_t number, const size_t brickNumber);
		static const bool isBallEnteredBlocksArea(const size_t ballNumber);
		static const bool isBallEnteredBricksArea(const size_t ballNumber);
		static void ballDivided(const size_t numbers);
		static const float getMainBallRadius();
		static const sf::Vector2f & getMainBallPosition();
		static const size_t getBallsAmount();

	protected:
		Ball();

	private:
		static std::mutex mutex;
		static std::shared_ptr<Ball> instance;
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		static void collision(const size_t);

		class BallContainer : public sf::Drawable {
		public:
			BallContainer();
			void determineUpdate();
			void ballMove(const sys::DPointf &);
			void setSpeedX(const float);
			void setSpeedY(const float);
			void setSpeed(const sf::Vector2f &);
			void setPos(const sf::Vector2f &);
			void setPos(const float, const float);
			void setRadius(const float);
			virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

			const bool isMain() const;
			const float getSpeedX() const;
			const float getSpeedY() const;
			const float getRad() const;
			const sf::Vector2f & getPos() const;

			bool left = false;
			bool right = false;
			bool bottom = false;
			bool top = false;
			bool broke = false;
			bool CD = false;
			bool active = false;

		private:
			void setColor(const sf::Color &);
			void resetBall();
			sf::Vector2f ballSpeed;
			sf::Vector2f oriSpeed;
			sf::Clock countTime;
			sf::Clock CDTime;
			sf::CircleShape ball;
			bool main = false;
		};

		static bool multiple;
		static bool ballStartC;
		static bool mainSettled;
		static bool initialize;
		static std::vector<std::unique_ptr<BallContainer>> balls;
	};
}
