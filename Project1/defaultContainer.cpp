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

void DefaultContainer::addChild(std::vector<std::shared_ptr<sf::Drawable>> elements) {
	children.insert(children.end(), elements.begin(), elements.end());
}

void DefaultContainer::addChildAt(std::vector<std::shared_ptr<sf::Drawable>> elements, int index) {
	children.insert(children.begin() + index, elements.begin(), elements.end());
}

bool DefaultContainer::contains(const sf::Drawable & element) const {
	return std::any_of(children.begin(), children.end(),
		[&element] (const std::shared_ptr<sf::Drawable> & child) {
		return child.get() == &element;
	});
}

int DefaultContainer::getChildrenCount() const {
	return children.size();
}
