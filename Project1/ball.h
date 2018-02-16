#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include "player.h"

namespace item {

	class Ball : public sf::Drawable {

	public:
		Ball(const Player &player);
		void initializeBall();
		void ballEnableMove(Player &player, sf::Sound &sound);
		void move(const Player &player);
		void flashRange(Player &player, sf::Sound &sound);
		void followPlayer(const Player &player);
		void ballCollided(const sf::FloatRect &bounds, const sf::Vector2f &speed);
		void ballCollided(const sf::Vector2f &speed);

		void setMainBallPosition(const sf::Vector2f &position);
		void setMainBallPosition(const float posX, const float posY);
		const sf::FloatRect getMainBallBounds() const;
		const float getMainBallRadius() const;
		const sf::Vector2f & getMainBallPosition() const;

	private:
		void flashElapsed(Player &);
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		class BallContent {
		public:
			BallContent(const Player &);
			BallContent();
			void ballMove(const sf::FloatRect &, const sf::Vector2f &);
			sf::Vector2f ballSpeed;
			sf::Vector2f tempSpeed;
			sf::CircleShape ball;
			void update(const sf::Vector2f &);
			bool left = false;
			bool right = false;
			bool bottom = false;
			bool top = false;
			bool broke = false;
		private:
			void setMainColor(const sf::Color &);
			void resetBall();
			bool main = false;
		};

		bool flash;
		sf::Clock elapsed;
		std::vector<BallContent*> balls;
	};
}

