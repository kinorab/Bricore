#pragma once

#include "container.h"

class DefaultContainer :
	public virtual Container {
public:
	DefaultContainer();
	virtual ~DefaultContainer() override;
	virtual void addChild(std::vector<std::shared_ptr<sf::Drawable>> children) override;
	virtual void addChildAt(std::vector<std::shared_ptr<sf::Drawable>> children, int index) override;
	virtual bool contains(const sf::Drawable & child) const override;
	virtual int getChildrenCount() const override;
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	std::vector<std::shared_ptr<sf::Drawable>> children;
};

