#pragma once

#include <SFML/Graphics.hpp>

class Player : public sf::Drawable {

public:
	explicit Player(const float playerSpeed);
	void playerMove();
	void setMainPlayerSpeed(const float playerSpeed);
	void setFlashPosition(const sf::Vector2f &position);
	void setFlashPosition(const float posX, const float posY);
	void setFlashFillColor(const sf::Color &color);

	const float getMainPlayerSpeed() const;
	const sf::Vector2f & getMainPlayerPosition() const;
	const sf::FloatRect getMainPlayerBounds() const;
	const sf::FloatRect getFlashBounds() const;

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	float mainPlayerSpeed;
	sf::RectangleShape mainPlayer;
	sf::RectangleShape redRange;
	sf::RectangleShape yellowRange;

	//sf::RectangleShape subPlayer;
};

