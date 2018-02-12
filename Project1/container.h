#pragma once

#include <memory>
#include <vector>
#include "displayObject.h"

class Container :
	public DisplayObject,
	public sf::Transformable{
public:
	Container();
	~Container() override;
	void addChild(std::unique_ptr<DisplayObject> child);
private:
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	std::vector<std::unique_ptr<DisplayObject>> children;
};

