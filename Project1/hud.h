#pragma once

#include "defaultContainer.h"
#include "rectangleShape.h"
#include "sprite.h"
#include <vector>
#include <SFML/Graphics.hpp>

class HUD :
	public DefaultContainer {
public:
	HUD();
private:
	std::shared_ptr<game::RectangleShape> background;
};