#pragma once

#include "player.h"
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

namespace item {

	class Ball : public sf::Drawable {

	public:
		explicit Ball(const Player &player);
		void ballUpdateMove(Player &player, sf::Sound &sound);
		void move(const Player &player);
		void followPlayer(const Player &player);
		void ballCollided(const sf::FloatRect &bounds, const sf::Vector2f &speed);
		bool ballCollided(const sf::FloatRect &bounds);
		void ballDivided(const size_t number);

	private:
		void initializeBall();
		void flashElapsed(Player &);
		void flashRange(Player &player, sf::Sound &sound);
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

		class BallContent {
		public:
			explicit BallContent(const Player &);
			explicit BallContent();
			void ballMove(const sf::FloatRect &, const sf::Vector2f &);
			void update();
			const bool isMain() const;

			sf::CircleShape ball;
			sf::Vector2f ballSpeed;
			bool left = false;
			bool right = false;
			bool bottom = false;
			bool top = false;
			bool broke = false;

		private:
			void setColor(const sf::Color &);
			void resetBall();
			sf::Vector2f oriSpeed;

			bool main = false;
			bool active = true;
		};

		bool flash;
		static bool initialize;
		sf::Clock elapsed;
		std::vector<std::unique_ptr<BallContent>> balls;
	};
}
