#pragma once

#include <SFML/Graphics.hpp>

class DisplayObject :
	public virtual sf::Drawable {
public:
	virtual ~DisplayObject() {}
};

