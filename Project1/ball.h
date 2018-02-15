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
		void ballMove(const Player &player);
		void flashRange(Player &player, sf::Sound &sound);
		void followPlayer(const Player &player);

		void setMainBallPosition(const sf::Vector2f &position);
		void setMainBallPosition(const float posX, const float posY);
		const sf::FloatRect & getMainBallBounds() const;
		const float getMainBallRadius() const;
		const sf::Vector2f & getMainBallPosition() const;

		static sf::Vector2f ballSpeed;

	private:
		void flashElapsed(Player &);
		void resetBall();
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		bool flash;
		sf::Clock elapsed;
		sf::CircleShape mainBall;
		std::vector <sf::CircleShape> balls;
	};
}

