#pragma once

#include "eventDispatcher.h"
#include <memory>
#include <SFML/Graphics.hpp>

class Container :
	public game::EventDispatcher,
	public sf::Drawable,
	public sf::Transformable {
public:
	Container();
	virtual ~Container() override;
	virtual void addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements);
	virtual void addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, int index);
	virtual bool contains(const sf::Drawable * element) const;
	virtual bool dispatchEvent(game::Event * event) override;
	virtual std::shared_ptr<sf::Drawable> getChildAt(int index) const;
	virtual int getChildIndex(const sf::Drawable * element) const;
	virtual int getChildrenCount() const;
	virtual void removeAllChildren();
	virtual void removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements);
	virtual void removeChildAt(std::vector<int> indexes);
	virtual void removeChildren(int beginIndex, int endIndex);
	virtual void setChildIndex(const sf::Drawable * element, int index);
	virtual void swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB);
	virtual void swapChildrenAt(int indexA, int indexB);
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
private:
	std::vector<std::shared_ptr<sf::Drawable>> children;
};
