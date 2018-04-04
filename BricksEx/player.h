#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player : public sf::Drawable {

public:
	explicit Player();
	static void playerMove(sf::Sound &sound, const sf::FloatRect &ballBounds);

	static const sf::Vector2f & getMainPlayerPos();
	static const sf::Vector2f getMainPlayerTopCenterPos();
	static const sf::FloatRect getMainPlayerBounds();

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	static void setFlashPosition(const sf::Vector2f &position);
	static void setFlashPosition(const float posX, const float posY);
	static void setFlashFillColor(const sf::Color &color);
	static void flashElapsed();
	static void flashRange(sf::Sound &sound, const sf::FloatRect &);

	static bool flash;
	static sf::Clock elapsed;
	static sf::RectangleShape mainPlayer;
	static sf::RectangleShape redRange;
	static sf::RectangleShape yellowRange;

	//sf::RectangleShape subPlayer;
};

