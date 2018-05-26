#include "container.h"
#include <algorithm>
#include "utility.h"
#include <stdexcept>

namespace game {
	Container::Container() {

	}

	Container::~Container() {
	}

	void Container::addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		addChildAt(elements, static_cast<int>(children.size()));
	}

	void Container::addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, const size_t index) {
		try {
			if (index > children.size()) {
				throw std::out_of_range("Index exceeds the size of children.");
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

				node->setParent(weak_from_this());
				return node;
			});
			children.insert(children.begin() + index, nodes.begin(), nodes.end());
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::addChildAt(): " << ex.what() << std::endl;
		}
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
		try {
			return children.at(index)->getDrawable();
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::getChildAt(): " << ex.what() << std::endl;
			return nullptr;
		}
	}

	size_t Container::getChildIndex(const sf::Drawable * element) const {
		for (size_t index = 0; index < children.size(); ++index) {
			if (children.at(index)->getDrawable().get() == element) {
				return index;
			}
		}

		throw std::out_of_range("Child not found.");
	}

	std::shared_ptr<InteractiveObject> Container::getChildNode(const sf::Drawable * element) const {
		try {
			return children.at(getChildIndex(element));
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::getChildNode(): " << ex.what() << std::endl;
			return nullptr;
		}
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

	std::vector<int> Container::removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		std::vector<int> indexes;
		try {
			std::transform(elements.begin(), elements.end(), std::back_inserter(indexes),
				[this](const std::shared_ptr<sf::Drawable> & element) {
				return static_cast<int>(getChildIndex(element.get()));
			});
			removeChildAt(indexes);
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::removeChild(): " << ex.what() << std::endl;
		}

		return indexes;
	}

	void Container::removeChildAt(std::vector<int> indexes) {
		std::sort(indexes.begin(), indexes.end());
		auto indexIterator = indexes.begin();
		children.erase(std::remove_if(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			if (indexIterator != indexes.end() && children[*indexIterator] == child) {
				++indexIterator;
				return true;
			}
			return false;
		}), children.end());
	}

	void Container::removeChildren(const int beginIndex, const int endIndex) {
		children.erase(children.begin() + beginIndex, children.begin() + endIndex);
	}

	void Container::setChildIndex(const sf::Drawable * element, const int index) {
		try {
			auto elementIterator = children.begin() + getChildIndex(element);
			std::move(elementIterator, elementIterator + 1, children.begin() + index);
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::setChildIndex(): " << ex.what() << std::endl;
		}
	}

	void Container::swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) {
		try {
			std::swap(children.at(getChildIndex(elementA)), children.at(getChildIndex(elementB)));
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::swapChildren(): " << ex.what() << std::endl;
		}
	}

	void Container::swapChildrenAt(const int indexA, const int indexB) {
		try {
			std::swap(children.at(indexA), children.at(indexB));
		}
		catch (std::out_of_range &ex) {
			std::cout << "Out_of_range in Container::swapChildrenAt(): " << ex.what() << std::endl;
		}
	}

	void Container::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		states.transform = states.transform.combine(getTransform());
		std::for_each(children.begin(), children.end(),
			[&](const std::shared_ptr<InteractiveObject> & child) {
			target.draw(*child, states);
		});
	}
}
