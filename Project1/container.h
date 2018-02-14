#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Container :
	public virtual sf::Drawable,
	public virtual sf::Transformable {
public:
	virtual ~Container() {}
	virtual void addChild(std::unique_ptr<sf::Drawable> child) = 0;
};

