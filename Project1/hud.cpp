#include "hud.h"

using namespace sf;

HUD::HUD(Texture &texture) {

	// vertices settle(position, color, texture coordinates)
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states){

	states.transform *= getTransform();
	states.texture = &image;
}
