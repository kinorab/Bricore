#pragma once

#include "../definition/diagonalPoint.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

namespace sf {
	class Sound;
	class RenderTarget;
	class RenderStates;
	class Color;
}

class Player :
	public sf::Drawable
	, public sf::Transformable {

public:
	Player();
	virtual void update(const sf::Vector2f &ballPos, const float ballRadius, const float updateRatio);
	virtual void setPlayerKey(const sf::Keyboard::Key left, const sf::Keyboard::Key right);

	virtual float getSpeed() const;
	virtual const sf::Vector2f & getPosition() const;
	virtual sf::Vector2f getTopCenterPos() const;
	virtual sf::FloatRect getGlobalBounds() const;
	virtual sys::DPointf getDP() const;
	virtual ~Player();

protected:
	virtual void setFlashPosition(const sf::Vector2f &);
	virtual void setFlashFillColor(const sf::Color &);
	virtual void flashElapsed();
	virtual void flashRange(sf::Sound &, const sf::Vector2f, const float);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	bool flash;
	bool flashCD;
	float speed;
	sf::Clock CDTime;
	sf::Clock elapsed;
	sf::RectangleShape board;
	sf::RectangleShape redRange;
	sf::RectangleShape yellowRange;
	sf::Keyboard::Key leftMoveKey;
	sf::Keyboard::Key rightMoveKey;
};

