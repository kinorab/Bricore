#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Container :
	public virtual sf::Drawable,
	public virtual sf::Transformable {
public:
	virtual ~Container() {}
	virtual void addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) = 0;
	virtual void addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, int index) = 0;
	virtual bool contains(const sf::Drawable & element) const = 0;
	virtual std::shared_ptr<sf::Drawable> getChildAt(int index) const = 0;
	virtual int getChildIndex(const sf::Drawable & element) const = 0;
	virtual int getChildrenCount() const = 0;
};

