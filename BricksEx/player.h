#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "diagonalPoint.h"

namespace sf {
	class Sound;
}

class Player : public sf::Drawable {

public:
	static std::shared_ptr<Player> getInstance();
	static std::shared_ptr<Player> getPredictInstance();
	static bool resetInstance();
	void update();

	const sf::Vector2f & getMainPlayerPos() const;
	const sf::Vector2f getMainPlayerTopCenterPos() const;
	const sf::FloatRect getMainPlayerBounds() const;
	const sys::DPointf getMainPlayerDP() const;
	const sys::DPointf getPlayerAreaDP() const;
protected:
	Player();

private:
	Player & operator =(const Player &);
	static std::shared_ptr<Player> instance;
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
	void setFlashPosition(const sf::Vector2f &position);
	void setFlashPosition(const float posX, const float posY);
	void setFlashFillColor(const sf::Color &color);
	void flashElapsed();
	void flashRange(sf::Sound &sound, const sf::Vector2f ballPos, const float radius);

	bool flash;
	sf::Clock elapsed;
	sf::RectangleShape mainPlayer;
	// sf::RectangleShape subPlayer;
	sf::RectangleShape redRange;
	sf::RectangleShape yellowRange;
	sf::RectangleShape playerArea;
};

