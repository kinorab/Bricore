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
	virtual bool contains(const sf::Drawable * element) const = 0;
	virtual std::shared_ptr<sf::Drawable> getChildAt(int index) const = 0;
	virtual int getChildIndex(const sf::Drawable * element) const = 0;
	virtual int getChildrenCount() const = 0;
	virtual void removeAllChildren() = 0;
	virtual void removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) = 0;
	virtual void removeChildAt(const std::vector<int> & indexes) = 0;
	virtual void removeChildren(int beginIndex, int endIndex) = 0;
	virtual void setChildIndex(const sf::Drawable * element, int index) = 0;
	virtual void swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) = 0;
	virtual void swapChildrenAt(int indexA, int indexB) = 0;
};

