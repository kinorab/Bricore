#pragma once

#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
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
		bool ballCollided(const sf::FloatRect &bounds);

	private:
		void flashElapsed(Player &);
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		class BallContent {
		public:
			explicit BallContent(const Player &);
			explicit BallContent();
			void ballMove(const sf::FloatRect &, const sf::Vector2f &);
			sf::Vector2f ballSpeed;
			sf::CircleShape ball;
			void update();
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
		std::vector<std::unique_ptr<BallContent>> balls;
	};
}
