#pragma once

#include "player.h"
#include <vector>
#include <memory>

namespace item {

	class Ball : public sf::Drawable {

	public:
		Ball();
		void update(const sf::FloatRect &playerBounds);
		void initializeBall();
		void followPlayer(const sf::Vector2f &playerPos);
		void ballCollided(const sf::FloatRect &bounds, const sf::Vector2f &speed);
		bool ballCollided(const sf::FloatRect &bounds);
		void ballDivided(const size_t numbers);
		const sf::FloatRect getMainBallBounds() const;
		const sf::Vector2f & getMainBallPosition() const;

	private:
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

		class BallContainer {
		public:
			BallContainer();
			void ballMove(const sf::FloatRect &);
			void update();
			const bool isMain() const;

			sf::CircleShape ball;
			sf::Vector2f ballSpeed;
			bool left = false;
			bool right = false;
			bool bottom = false;
			bool top = false;
			bool broke = false;
			bool CD = false;

		private:
			void setColor(const sf::Color &);
			void resetBall();
			sf::Vector2f oriSpeed;
			sf::Clock countTime;
			sf::Clock CDTime;
			bool main = false;
			bool active = false;
		};

		static bool mainSettled;
		static bool initialize;
		std::vector<std::unique_ptr<BallContainer>> balls;
	};
}
