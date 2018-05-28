#include "interactiveObject.h"
#include "container.h"
#include "utility.h"
#include <algorithm>

namespace game {
	InteractiveObject::InteractiveObject()
		:idCount(0) {
	}

	InteractiveObject::~InteractiveObject() {
	}

	int InteractiveObject::addEventListener(sf::Event::EventType type, std::function<void(Event *)> callback) {
		return addEventListener(type, callback, false);
	}

	int InteractiveObject::addEventListener(sf::Event::EventType type, std::function<void(Event *)> callback, bool useCapture) {
		listeners[idCount] = EventListener{ type, callback, useCapture };
		int returnId = idCount;
		idCount += 1;
		return returnId;
	}

	bool InteractiveObject::dispatchEvent(Event * event) {
		Event::DispatchHelper helper(event);
		helper.setCurrentTarget(this);

		if (event->getPhase() == EventPhase::NONE) {
			helper.setTarget(this);
			helper.setPhase(EventPhase::CAPTURING_PHASE);
		}

		if (event->getPhase() == EventPhase::CAPTURING_PHASE && !getParent().expired()) {
			getParent().lock()->dispatchEvent(event);
			helper.setCurrentTarget(this);
		}

		if (event->getCurrentTarget() == event->getTarget()) {
			helper.setPhase(EventPhase::AT_TARGET);
		}

		if (!helper.isPropagationStopped()) {
			std::map<int, EventListener> tempListeners = listeners;
			std::for_each(tempListeners.begin(), tempListeners.end(),
				[&](const std::pair<const int, EventListener> & listener) {
				if (event->getType() == listener.second.type
					&& !((event->getPhase() == EventPhase::CAPTURING_PHASE && !listener.second.useCapture)
						|| (event->getPhase() == EventPhase::BUBBLING_PHASE && listener.second.useCapture))) {
					listener.second.callback(event);
				}
			});
		}

		if (event->getCurrentTarget() == event->getTarget()) {
			helper.setPhase(EventPhase::BUBBLING_PHASE);
		}

		if (event->getPhase() == EventPhase::BUBBLING_PHASE && event->getBubbles() && !getParent().expired()) {
			getParent().lock()->dispatchEvent(event);
			helper.setCurrentTarget(this);
		}

		if (event->getCurrentTarget() == event->getTarget()) {
			helper.setPhase(EventPhase::NONE);
		}

		return !event->getDefaultPrevented();
	}

	std::weak_ptr<Container> InteractiveObject::getParent() {
		if (parent.expired() && parentRaw != nullptr) {
			parent = parentRaw->weak_from_this();
		}

		return parent;
	}

	void InteractiveObject::initialize() {

	}

	void InteractiveObject::removeEventListener(int id) {
		listeners.erase(std::find_if(listeners.begin(), listeners.end(),
			[&](std::pair<const int, EventListener> & listener) {
			return listener.first == id;
		}));
	}

	void InteractiveObject::setParent(Container * container) {
		if (container == nullptr) {
			parentRaw = nullptr;
			return;
		}

		parent = std::move(container->weak_from_this());
		if (parent.expired()) {
			parentRaw = container;
		}
		else {
			parentRaw = nullptr;
		}
	}

	void InteractiveObject::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		target.draw(*getDrawable(), states.transform.combine(getTransform()));
	}
}