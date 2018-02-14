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
		[&](const std::shared_ptr<sf::Drawable> & child) {
		target.draw(*child, getTransform());
	});
}

void DefaultContainer::addChild(std::vector<std::shared_ptr<sf::Drawable>> children) {
	this->children.insert(this->children.end(), children.begin(), children.end());
}

void DefaultContainer::addChildAt(std::vector<std::shared_ptr<sf::Drawable>> children, int index) {
	this->children.insert(this->children.begin() + index, children.begin(), children.end());
}

bool DefaultContainer::contains(const sf::Drawable & child) const {
	std::find(chil)
}

int DefaultContainer::getChildrenCount() const {
	return children.size();
}
