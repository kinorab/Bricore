#pragma once

#include "defaultContainer.h"
#include <SFML/Graphics.hpp>
#include <vector>

class HUD :
	// put text class into hud
	public DefaultContainer {
public:

	explicit HUD(sf::Texture &);

private:

	sf::Texture image;
	std::vector <sf::VertexArray> vertices;
};