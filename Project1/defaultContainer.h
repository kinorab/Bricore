#pragma once

#include "container.h"

class DefaultContainer :
	public virtual Container {
public:
	DefaultContainer();
	virtual ~DefaultContainer() override;
	virtual void addChild(std::unique_ptr<sf::Drawable> child) override;
protected:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	std::vector<std::unique_ptr<sf::Drawable>> children;
};

