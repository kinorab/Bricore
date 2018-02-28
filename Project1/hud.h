#pragma once

#include "defaultContainer.h"
#include <SFML/Graphics.hpp>
#include <vector>

class HUD :
	// put text class into hud
	public DefaultContainer {
public:

	explicit HUD();

private:

	std::shared_ptr<sf::RectangleShape> background;
};