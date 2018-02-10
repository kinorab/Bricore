#pragma once

#include <SFML/Graphics.hpp>

class SceneNode
	:public sf::Transformable,
	public sf::Drawable{
public:
	virtual void addChild(SceneNode * child) = 0;
	virtual ~SceneNode() {}
};

