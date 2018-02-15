#pragma once

#include "container.h"

class DefaultContainer :
	public virtual Container {
public:
	DefaultContainer();
	virtual ~DefaultContainer() override;
	virtual void addChild(const std::vector<std::shared_ptr<sf::Drawable>> & children) override;
	virtual void addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & children, int index) override;
	virtual bool contains(const sf::Drawable & element) const override;
	virtual std::shared_ptr<sf::Drawable> getChildAt(int index) const override;
	virtual int getChildIndex(const sf::Drawable & element) const override;
	virtual int getChildrenCount() const override;
	virtual void removeAllChildren() override;
	virtual void removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) override;
	virtual void removeChildAt(const std::vector<int> & indexes) override;
	virtual void removeChildren(int beginIndex, int endIndex) override;
	virtual void setChildIndex(const sf::Drawable & element, int index) override;
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	std::vector<std::shared_ptr<sf::Drawable>> children;
};

