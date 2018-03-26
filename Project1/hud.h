#pragma once

#include "container.h"
#include "rectangleShape.h"
#include "sprite.h"
#include <vector>
#include <SFML/Graphics.hpp>

class HUD :
	public Container {
public:
	HUD();
private:
	std::shared_ptr<game::RectangleShape> background;
};