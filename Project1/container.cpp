#include "container.h"
#include <algorithm>

Container::Container() {
}

Container::~Container()
{
}

void Container::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	std::for_each(children.begin(), children.end(),
		[&](const std::unique_ptr<DisplayObject> & child) {
		target.draw(*child, getTransform());
	});
}

void Container::addChild(std::unique_ptr<DisplayObject> child) {
	children.push_back(std::move(child));
}

