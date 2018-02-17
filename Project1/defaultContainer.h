#pragma once

#include "container.h"

class DefaultContainer :
	public virtual Container {
public:
	DefaultContainer();
	virtual ~DefaultContainer() override;
	virtual void addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) override;
	virtual void addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, int index) override;
	virtual void addEventListener() override;
	virtual bool contains(const sf::Drawable * element) const override;
	virtual std::shared_ptr<sf::Drawable> getChildAt(int index) const override;
	virtual int getChildIndex(const sf::Drawable * element) const override;
	virtual int getChildrenCount() const override;
	virtual bool hasEventListener() override;
	virtual void removeAllChildren() override;
	virtual void removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) override;
	virtual void removeChildAt(std::vector<int> indexes) override;
	virtual void removeChildren(int beginIndex, int endIndex) override;
	virtual void removeEventListener() override;
	virtual void setChildIndex(const sf::Drawable * element, int index) override;
	virtual void swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) override;
	virtual void swapChildrenAt(int indexA, int indexB) override;
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	std::vector<std::shared_ptr<sf::Drawable>> children;
};
