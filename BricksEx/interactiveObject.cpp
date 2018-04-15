#include "interactiveObject.h"
#include "container.h"
#include <algorithm>

namespace game {
	InteractiveObject::~InteractiveObject() {
	}

	void InteractiveObject::addEventListener(sf::Event::EventType type, std::function<void(Event*)> callback) {
		addEventListener(type, callback, false);
	}

	void InteractiveObject::addEventListener(sf::Event::EventType type, std::function<void(Event *)> callback, bool useCapture) {
		removeEventListener(type, callback, useCapture);
		listeners.push_back(EventListener{ type, callback, useCapture });
	}

	bool InteractiveObject::dispatchEvent(Event * event) {
		Event::DispatchHelper helper(event);
		helper.setCurrentTarget(this);

		if (event->getPhase() == EventPhase::NONE) {
			helper.setTarget(this);
			helper.setPhase(EventPhase::CAPTURING_PHASE);
		}

		if (event->getPhase() == EventPhase::CAPTURING_PHASE && !parent.expired()) {
			parent.lock()->dispatchEvent(event);
			helper.setCurrentTarget(this);
		}

		if (event->getCurrentTarget() == event->getTarget()) {
			helper.setPhase(EventPhase::AT_TARGET);
		}

		if (!helper.isPropagationStopped()) {
			std::vector<EventListener> tempListeners = listeners;
			std::for_each(tempListeners.begin(), tempListeners.end(),
				[&](const EventListener & listener) {
				if (event->getType() == listener.type
					&& !((event->getPhase() == EventPhase::CAPTURING_PHASE && !listener.useCapture)
						|| (event->getPhase() == EventPhase::BUBBLING_PHASE && listener.useCapture))) {
					listener.callback(event);
				}
			});
		}

		if (event->getCurrentTarget() == event->getTarget()) {
			helper.setPhase(EventPhase::BUBBLING_PHASE);
		}

		if (event->getPhase() == EventPhase::BUBBLING_PHASE && event->getBubbles() && !parent.expired()) {
			parent.lock()->dispatchEvent(event);
			helper.setCurrentTarget(this);
		}

		if (event->getCurrentTarget() == event->getTarget()) {
			helper.setPhase(EventPhase::NONE);
		}

		return !event->getDefaultPrevented();
	}

	std::weak_ptr<Container> InteractiveObject::getParent() const {
		return parent;
	}

	void InteractiveObject::initialize() {

	}

	void InteractiveObject::removeEventListener(sf::Event::EventType type, std::function<void(Event *)> callback, bool useCapture) {
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
			[&](EventListener & listener) {
			return listener.type == type
				&& *listener.callback.target<void(Event *)>() == *callback.target<void(Event *)>()
				&& listener.useCapture == useCapture;
		}), listeners.end());
	}

	void InteractiveObject::setParent(std::weak_ptr<Container> container) {
		parent = std::move(container);
	}

	void InteractiveObject::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		target.draw(*getDrawable(), states.transform.combine(getTransform()));
	}
}