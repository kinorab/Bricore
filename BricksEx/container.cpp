#include "container.h"
#include <algorithm>

namespace game {
	struct Container::EventListener {
		std::string type;
		std::function<void(Event *)> callback;
		bool useCapture;
	};

	Container::Container() {

	}

	Container::~Container() {
	}

	void Container::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		std::for_each(children.begin(), children.end(),
			[&](const std::shared_ptr<sf::Drawable> & child) {
			target.draw(*child, getTransform());
		});
	}

	void Container::addChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		addChildAt(elements, children.size());
	}

	void Container::addChildAt(const std::vector<std::shared_ptr<sf::Drawable>> & elements, size_t index) {
		std::for_each(elements.begin(), elements.end(),
			[&](const std::shared_ptr<sf::Drawable> & element) {
			Container * container = dynamic_cast<Container *>(element.get());
			if (container) {
				container->setParent(weak_from_this());
			}
		});
		children.insert(children.begin() + index, elements.begin(), elements.end());
	}

	void Container::addEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture) {
		removeEventListener(type, callback, useCapture);
		listeners.push_back(EventListener{ type, callback, useCapture });
	}

	bool Container::contains(const sf::Drawable * element) const {
		return std::any_of(children.begin(), children.end(),
			[&](const std::shared_ptr<sf::Drawable> & child) {
			return child.get() == element;
		});
	}

	bool Container::dispatchEvent(Event * event) {
		Event::DispatchHelper helper(event);
		helper.setCurrentTarget(this);
		if (event->getPhase() == EventPhase::NONE) {
			return true;
		}

		std::vector<EventListener> tempListeners = listeners;
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](const EventListener & listener) {
			if (!(event->getPhase() == EventPhase::CAPTURING_PHASE && !listener.useCapture)
				|| ((event->getPhase() == EventPhase::BUBBLING_PHASE && listener.useCapture))) {
				listener.callback(event);
			}
		});

		return !event->getDefaultPrevented();
	}

	std::shared_ptr<sf::Drawable> Container::getChildAt(int index) const {
		return children[index];
	}

	int Container::getChildIndex(const sf::Drawable * element) const {
		return std::find_if(children.begin(), children.end(),
			[&](const std::shared_ptr<sf::Drawable> & child) {
			return child.get() == element;
		}) - children.begin();
	}

	int Container::getChildrenCount() const {
		return children.size();
	}

	std::weak_ptr<Container> Container::getParent() const {
		return parent;
	}

	void Container::removeAllChildren() {
		children.clear();
		children.shrink_to_fit();
	}

	void Container::removeChild(const std::vector<std::shared_ptr<sf::Drawable>> & elements) {
		std::vector<int> indexes;
		std::transform(elements.begin(), elements.end(), std::back_inserter(indexes),
			[&](const std::shared_ptr<sf::Drawable> & element) {
			return getChildIndex(element.get());
		});
		removeChildAt(indexes);
	}

	void Container::removeChildAt(std::vector<int> indexes) {
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

	void Container::removeChildren(int beginIndex, int endIndex) {
		children.erase(children.begin() + beginIndex, children.begin() + endIndex);
	}

	void Container::removeEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture) {
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
			[&](EventListener & listener) {
			return listener.type == type
				&& *listener.callback.target<void(Event *)>() == *callback.target<void(Event *)>()
				&& listener.useCapture == useCapture;
		}));
	}

	void Container::setChildIndex(const sf::Drawable * element, int index) {
		auto elementIterator = children.begin() + getChildIndex(element);
		std::move(elementIterator, elementIterator + 1, children.begin() + index);
	}

	void Container::setParent(std::weak_ptr<Container> container) {
		parent = std::move(container);
	}

	void Container::swapChildren(const sf::Drawable * elementA, const sf::Drawable * elementB) {
		std::swap(children[getChildIndex(elementA)], children[getChildIndex(elementB)]);
	}

	void Container::swapChildrenAt(int indexA, int indexB) {
		std::swap(children[indexA], children[indexB]);
	}
}
