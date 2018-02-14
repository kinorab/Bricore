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

void DefaultContainer::addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
	children.insert(children.end(), elements.begin(), elements.end());
}

void DefaultContainer::addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, int index) {
	children.insert(children.begin() + index, elements.begin(), elements.end());
}

bool DefaultContainer::contains(const sf::Drawable & element) const {
	return std::any_of(children.begin(), children.end(),
		[&element] (const std::shared_ptr<sf::Drawable> & child) {
		return child.get() == &element;
	});
}

std::shared_ptr<sf::Drawable> DefaultContainer::getChildAt(int index) const {
	return std::shared_ptr<sf::Drawable>();
}

int DefaultContainer::getChildIndex(const sf::Drawable & element) const {
	return std::find_if(children.begin(), children.end(),
		[&element](const std::shared_ptr<sf::Drawable> & child) {
		return child.get() == &element;
	}) - children.begin();
}

int DefaultContainer::getChildrenCount() const {
	return children.size();
}
