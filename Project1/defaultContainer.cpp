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

void DefaultContainer::addEventListener() {

}

bool DefaultContainer::contains(const sf::Drawable * element) const {
	return std::any_of(children.begin(), children.end(),
		[&](const std::shared_ptr<sf::Drawable> & child) {
		return child.get() == element;
	});
}

std::shared_ptr<sf::Drawable> DefaultContainer::getChildAt(int index) const {
	return children[index];
}

int DefaultContainer::getChildIndex(const sf::Drawable * element) const {
	return std::find_if(children.begin(), children.end(),
		[&](const std::shared_ptr<sf::Drawable> & child) {
		return child.get() == element;
	}) - children.begin();
}

int DefaultContainer::getChildrenCount() const {
	return children.size();
}

bool DefaultContainer::hasEventListener() {
	return false;
}

void DefaultContainer::removeAllChildren() {
	children.clear();
	children.shrink_to_fit();
}

void DefaultContainer::removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
	std::vector<int> indexes;
	std::transform(elements.begin(), elements.end(), std::back_inserter(indexes),
		[&](const std::shared_ptr<sf::Drawable> & element) {
		return getChildIndex(element.get());
	});
	removeChildAt(indexes);
}

void DefaultContainer::removeChildAt(std::vector<int> indexes) {
	std::sort(indexes.begin(), indexes.end());
	auto indexIterator = indexes.begin();
	children.erase(std::remove_if(children.begin(), children.end(),
		[&](const std::shared_ptr<sf::Drawable> & child) {
		if (children[*indexIterator] == child) {
			indexIterator += 1;
			return true;
		}
		return false;
	}));
}

void DefaultContainer::removeChildren(int beginIndex, int endIndex) {
	children.erase(children.begin() + beginIndex, children.begin() + endIndex);
}

void DefaultContainer::removeEventListener() {

}

void DefaultContainer::setChildIndex(const sf::Drawable * element, int index) {
	auto elementIterator = children.begin() + getChildIndex(element);
	std::move(elementIterator, elementIterator + 1, children.begin() + index);
}

void DefaultContainer::swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) {
	std::swap(children[getChildIndex(elementA)], children[getChildIndex(elementB)]);
}

void DefaultContainer::swapChildrenAt(int indexA, int indexB) {
	std::swap(children[indexA], children[indexB]);
}
