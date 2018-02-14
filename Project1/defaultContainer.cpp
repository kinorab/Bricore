#include "defaultContainer.h"
#include <algorithm>

DefaultContainer::DefaultContainer()
{
}


DefaultContainer::~DefaultContainer()
{
}


void DefaultContainer::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	std::for_each(children.begin(), children.end(),
		[&](const std::unique_ptr<sf::Drawable> & child) {
		target.draw(*child, getTransform());
	});
}

void DefaultContainer::addChild(std::unique_ptr<sf::Drawable> child) {
	children.push_back(std::move(child));
}
