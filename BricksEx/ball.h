#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "diagonalPoint.h"

namespace item {
	class Ball : public sf::Drawable {

	public:
		static std::shared_ptr<Ball> getInstance();
		static std::shared_ptr<Ball> getPredictInstance();
		static const bool resetInstance();
		void update();
		void initializeBall();
		void followPlayer();
		void ballCollided(const size_t number, const size_t blockNumber);
		const bool isBallCollided(const size_t number, const size_t brickNumber);
		const bool isBallEnteredBlocksArea(const size_t ballNumber) const;
		const bool isBallEnteredBricksArea(const size_t ballNumber) const;
		void ballDivided(const size_t numbers);

		const float getMainBallRadius() const;
		const sf::Vector2f & getMainBallPosition() const;
		const size_t getBallsAmount() const;

	protected:
		Ball();

	private:
		Ball & operator =(const Ball &);
		static std::shared_ptr<Ball> instance;
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
		void collision(const size_t);

		class BallContainer : public sf::Drawable {
		public:
			BallContainer();
			void determineUpdate();
			void move(const sys::DPointf &);
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

			bool left;
			bool right;
			bool bottom;
			bool top;
			bool broke;
			bool CD;
			bool active;

		private:
			void setColor(const sf::Color &);
			void resetBall();
			bool main;
			sf::Vector2f ballSpeed;
			sf::Vector2f oriSpeed;
			sf::Clock countTime;
			sf::Clock CDTime;
			sf::CircleShape ball;
		};

		bool multiple;
		bool ballStartC;
		static bool mainSettled;
		static bool initialize;
		std::vector<std::shared_ptr<BallContainer>> balls;
	};
}
