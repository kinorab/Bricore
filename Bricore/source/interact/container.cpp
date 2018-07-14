#include "container.h"
#include "../definition/utility.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <map>

namespace game {
	Container::Container() noexcept {

	}

	Container::~Container() {
		std::for_each(children.begin(), children.end(),
			[](const std::shared_ptr<InteractiveObject> & child) {
			child->setParent(nullptr);
		});
	}

	void Container::addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		addChildAt(elements, static_cast<int>(children.size()));
	}

	void Container::addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, const size_t index) {
		if (index > children.size()) {
			throw std::out_of_range("Index not in the range of children.");
		}

		std::vector<std::shared_ptr<InteractiveObject>> nodes;
		std::transform(elements.begin(), elements.end(), std::back_inserter(nodes),
			[this](const std::shared_ptr<sf::Drawable> & element) {
			std::shared_ptr<InteractiveObject> node;
			if (dynamic_cast<InteractiveObject *>(element.get())) {
				node = std::dynamic_pointer_cast<InteractiveObject>(element);
			}
			else if (dynamic_cast<sf::CircleShape *>(element.get())) {
				node.reset(new CircleShapeNode(std::dynamic_pointer_cast<sf::CircleShape>(element)));
			}
			else if (dynamic_cast<sf::RectangleShape *>(element.get())) {
				node.reset(new RectangleShapeNode(std::dynamic_pointer_cast<sf::RectangleShape>(element)));
			}
			else if (dynamic_cast<sf::Sprite *>(element.get())) {
				node.reset(new SpriteNode(std::dynamic_pointer_cast<sf::Sprite>(element)));
			}
			else if (dynamic_cast<sf::VertexArray *>(element.get())) {
				node.reset(new VertexArrayNode(std::dynamic_pointer_cast<sf::VertexArray>(element)));
			}
			else {
				node.reset(new DrawableNode(element));
			}

			if (node->getParent() != nullptr) {
				node->getParent()->removeChild({ node });
			}

			node->setParent(this);
			return node;
		});
		children.insert(children.begin() + index, nodes.begin(), nodes.end());
	}

	bool Container::contains(const sf::Drawable * element) const {
		return std::any_of(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			return child->getDrawable().get() == element;
		});
	}

	bool Container::containsPoint(const sf::Vector2f & point) const {
		return std::any_of(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			return child->containsPoint(point);
		});
	}

	std::shared_ptr<sf::Drawable> Container::getChildAt(int index) const {
		return children[index]->getDrawable();
	}

	size_t Container::getChildIndex(const sf::Drawable * element) const {
		for (size_t index = 0; index < children.size(); ++index) {
			if (children[index]->getDrawable().get() == element) {
				return index;
			}
		}

		throw std::invalid_argument("Child doesn't exist.");
	}

	std::shared_ptr<InteractiveObject> Container::getChildNode(const sf::Drawable * element) const {
		return children[getChildIndex(element)];
	}

	size_t Container::getChildrenCount() const {
		return children.size();
	}

	std::shared_ptr<InteractiveObject> Container::getObjectUnderPoint(const sf::Vector2f & point) {
		std::shared_ptr<Container> node = shared_from_this();
		bool found = false;
		do {
			for (auto child = node->children.rbegin(); child != node->children.rend(); child += 1) {
				if (!(*child)->containsPoint(point)) {
					continue;
				}

				found = true;
				if (!dynamic_cast<Container *>(child->get())) {
					return *child;
				}

				node = std::dynamic_pointer_cast<Container>(*child);
				break;
			}
		} while (found);

		return nullptr;
	}

	std::shared_ptr<sf::Drawable> Container::getDrawable() const {
		return std::const_pointer_cast<sf::Drawable>(std::static_pointer_cast<const sf::Drawable>(shared_from_this()));
	}

	void Container::removeAllChildren(const bool isRemoveChlidrenListener) {
		std::for_each(children.begin(), children.end(),
			[=](const std::shared_ptr<InteractiveObject> & child) {
			child->setParent(nullptr);
			if (isRemoveChlidrenListener) {
				child->removeAllListener();
			}
		});
		children.clear();
		children.shrink_to_fit();
	}

	std::vector<int> Container::removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		std::vector<int> indexes;
		std::for_each(elements.begin(), elements.end(),
			[&](const std::shared_ptr<sf::Drawable> & element) {
			try {
				indexes.push_back(static_cast<int>(getChildIndex(element.get())));
			}
			catch (std::invalid_argument &ex) {
				std::cout << "Invalid_argument: " << ex.what() << " in Container::removeChild(): " << std::endl;
			}
		});
		removeChildAt(indexes);
		return indexes;
	}

	void Container::removeChildAt(std::vector<int> indexes) {
		std::sort(indexes.begin(), indexes.end());
		auto indexIterator = indexes.begin();
		children.erase(std::remove_if(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			if (indexIterator != indexes.end() && children[*indexIterator] == child) {
				child->setParent(nullptr);
				++indexIterator;
				return true;
			}

			return false;
		}), children.end());
	}

	void Container::removeChildren(const int beginIndex, const int endIndex) {
		std::for_each(children.begin() + beginIndex, children.begin() + endIndex,
			[](const std::shared_ptr<InteractiveObject> & child) {
			child->setParent(nullptr);
		});
		children.erase(children.begin() + beginIndex, children.begin() + endIndex);
		children.shrink_to_fit();
	}

	void Container::removeInvalidChildren() {
		children.erase(std::remove_if(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			if (!child) return true;
			return false;
		}), children.end());
	}

	void Container::replaceChild(const std::vector<std::shared_ptr<sf::Drawable>>& elements, const std::vector<int> indexes) {
		std::map<int, std::shared_ptr<sf::Drawable>> elementMap;
		std::transform(indexes.begin(), indexes.end(), elements.begin(), std::inserter(elementMap, elementMap.end()),
			[](const int index, const std::shared_ptr<sf::Drawable> element) {
			return std::make_pair(index, element);
		});
		removeChildAt(indexes);
		std::for_each(indexes.begin(), indexes.end(),
			[&](const int index) {
			addChildAt({ elementMap[index] }, index);
		});
	}

	void Container::setChildIndex(const sf::Drawable * element, const int index) {
		auto elementIterator = children.begin() + getChildIndex(element);
		std::move(elementIterator, elementIterator + 1, children.begin() + index);
	}

	void Container::swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) {
		std::swap(children[getChildIndex(elementA)], children[getChildIndex(elementB)]);
	}

	void Container::swapChildrenAt(const int indexA, const int indexB) {
		std::swap(children[indexA], children[indexB]);
	}

	void Container::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		std::for_each(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			target.draw(*child, states);
		});
	}
}
