#pragma once

#include <memory>
#include "displayObject.h"

class Container :
	public virtual DisplayObject,
	public virtual sf::Transformable{
public:
	virtual ~Container() {}
	virtual void addChild(std::unique_ptr<DisplayObject> child) = 0;
};

