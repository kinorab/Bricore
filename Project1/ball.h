#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace item {
	class Ball : public sf::Drawable {

	public:
		Ball(sf::Shape &player);
		void initializeBall();
		void resetBall();
		void ballEnableMove(sf::Shape &player, sf::Shape &range, sf::Sound &sound);
		void ballMove(sf::Shape &player);
		void flashRange(sf::Shape &player, sf::Shape &range, sf::Sound &sound, bool &flash);

	protected:
		sf::Vector2f ballSpeed;

	private:
		inline void flashElapsed(sf::Shape &range, bool &flash);
		virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

		sf::Clock elapsed;
		sf::CircleShape mainBall;
		std::vector <sf::CircleShape> balls;
	};
}

