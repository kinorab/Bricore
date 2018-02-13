#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class HUD :
	// put text class into hud
	public sf::Drawable,
	public sf::Transformable {
public:

	explicit HUD(sf::Texture &);

private:

	virtual void draw(sf::RenderTarget &, sf::RenderStates);
	sf::Texture image;
	std::vector <sf::Vertex> vertices;
};