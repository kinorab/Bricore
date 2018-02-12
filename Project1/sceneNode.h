#pragma once

#include <SFML/Graphics.hpp>

class SceneNode :
	public sf::Transformable,
	public sf::Drawable {
public:
	virtual ~SceneNode() {}
};

