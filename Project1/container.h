#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Container :
	public virtual sf::Drawable,
	public virtual sf::Transformable {
public:
	virtual ~Container() {}
	virtual void addChild(std::vector<std::shared_ptr<sf::Drawable>> children) = 0;
	virtual void addChildAt(std::vector<std::shared_ptr<sf::Drawable>> children, int index) = 0;
	virtual bool contains(const sf::Drawable & child) const = 0;
	virtual int getChildrenCount() const = 0;
};

