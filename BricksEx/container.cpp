#include "container.h"
#include <algorithm>

namespace game {
	Container::Container() {

	}

	Container::~Container() {
	}

	void Container::addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		addChildAt(elements, children.size());
	}

	void Container::addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, size_t index) {
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
			else if (dynamic_cast<sf::VertexArray *>(element.get())) {
				node.reset(new VertexArrayNode(std::dynamic_pointer_cast<sf::VertexArray>(element)));
			}
			else {
				node.reset(new DrawableNode(element));
			}

			node->setParent(weak_from_this());
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
			return child->containsPoint(getTransform().getInverse().transformPoint(point));
		});
	}

	std::shared_ptr<sf::Drawable> Container::getChildAt(int index) const {
		return children[index]->getDrawable();
	}

	int Container::getChildIndex(const sf::Drawable * element) const {
		return std::find_if(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			return child->getDrawable().get() == element;
		}) - children.begin();
	}

	std::shared_ptr<InteractiveObject> Container::getChildNode(const sf::Drawable * element) const {
		return children[getChildIndex(element)];
	}

	int Container::getChildrenCount() const {
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

	void Container::initialize() {
		std::for_each(children.begin(), children.end(),
			[this](std::shared_ptr<InteractiveObject> & child) {
			child->setParent(weak_from_this());
			child->initialize();
		});
	}

	void Container::removeAllChildren() {
		children.clear();
		children.shrink_to_fit();
	}

	void Container::removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		std::vector<int> indexes;
		std::transform(elements.begin(), elements.end(), std::back_inserter(indexes),
			[this](const std::shared_ptr<sf::Drawable> & element) {
			return getChildIndex(element.get());
		});
		removeChildAt(indexes);
	}

	void Container::removeChildAt(std::vector<int> indexes) {
		std::sort(indexes.begin(), indexes.end());
		auto indexIterator = indexes.begin();
		children.erase(std::remove_if(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			if (children[*indexIterator] == child) {
				indexIterator += 1;
				return true;
			}
			return false;
		}), children.end());
	}

	void Container::removeChildren(int beginIndex, int endIndex) {
		children.erase(children.begin() + beginIndex, children.begin() + endIndex);
	}

	void Container::setChildIndex(const sf::Drawable * element, int index) {
		auto elementIterator = children.begin() + getChildIndex(element);
		std::move(elementIterator, elementIterator + 1, children.begin() + index);
	}

	void Container::swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) {
		std::swap(children[getChildIndex(elementA)], children[getChildIndex(elementB)]);
	}

	void Container::swapChildrenAt(int indexA, int indexB) {
		std::swap(children[indexA], children[indexB]);
	}

	void Container::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		states.transform = states.transform.combine(getTransform());
		std::for_each(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			target.draw(*child, states);
		});
	}
}
