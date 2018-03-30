#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player : public sf::Drawable {

public:
	explicit Player(const float playerSpeed);
	void playerMove(sf::Sound &sound, const sf::FloatRect &ballBounds, const sf::Vector2f &mainBallPos);
	void setMainPlayerSpeed(const float playerSpeed);
	void setFlashPosition(const sf::Vector2f &position);
	void setFlashPosition(const float posX, const float posY);
	void setFlashFillColor(const sf::Color &color);

	const float getMainPlayerSpeed() const;
	const sf::Vector2f & getMainPlayerPos() const;
	const sf::Vector2f getMainPlayerTopCenterPos() const;
	const sf::FloatRect getMainPlayerBounds() const;
	const sf::FloatRect getFlashBounds() const;

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	void flashElapsed();
	void flashRange(sf::Sound &sound, const sf::FloatRect &, const sf::Vector2f &);

	float mainPlayerSpeed;
	static bool flash;
	sf::Clock elapsed;
	sf::RectangleShape mainPlayer;
	sf::RectangleShape redRange;
	sf::RectangleShape yellowRange;

	//sf::RectangleShape subPlayer;
};

