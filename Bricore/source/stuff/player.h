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
namespace game {
	class Level;
}

class Player :
	public sf::Drawable
	, public sf::Transformable {

public:
	Player();
	void update(const sf::Vector2f &ballPos, const float ballRadius, const float updateRatio);
	void setPlayerKey(const sf::Keyboard::Key left, const sf::Keyboard::Key right);

	float getSpeed() const;
	const sf::Vector2f & getPosition() const;
	sf::Vector2f getTopCenterPos() const;
	sf::FloatRect getGlobalBounds() const;
	sys::DPointf getDP() const;
	virtual ~Player();

protected:
	void setFlashPosition(const sf::Vector2f &);
	void setFlashFillColor(const sf::Color &);
	void flashElapsed();
	void flashRange(sf::Sound & sound, const sf::Vector2f ballPos, const float radius);

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	bool bFlash;
	bool bFlashCD;
	float fSpeed;
	sf::Clock CDTime;
	sf::Clock elapsed;
	sf::RectangleShape board;
	sf::RectangleShape redRange;
	sf::RectangleShape yellowRange;
	sf::Keyboard::Key leftMoveKey;
	sf::Keyboard::Key rightMoveKey;
};

