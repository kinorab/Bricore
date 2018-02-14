#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace item {
	class Ball : public sf::Drawable {

	public:
		Ball(sf::Shape &player);
		void initializeBall();
		void ballEnableMove(const sf::Shape &player, sf::Shape &range, sf::Sound &sound);
		void ballMove(const sf::Shape &player);
		void flashRange(const sf::Shape &player, sf::Shape &range, sf::Sound &sound);
		void followPlayer(const sf::Shape &player);

		void setMainBallPosition(const sf::Vector2f &position);
		void setMainBallPosition(const float posX, const float posY);
		const sf::FloatRect getMainBallBound() const;
		const float getMainBallRadius() const;
		const sf::Vector2f & getMainBallPosition() const;

		static sf::Vector2f ballSpeed;

	private:
		void flashElapsed(sf::Shape &range);
		void resetBall();
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		bool flash;
		sf::Clock elapsed;
		sf::CircleShape mainBall;
		std::vector <sf::CircleShape> balls;
	};
}

