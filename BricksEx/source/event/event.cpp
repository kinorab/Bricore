#include "event.h"

namespace game {
	Event::Event(EventType type, bool bubbles, bool cancelable) :
		bubbles(bubbles),
		cancelable(cancelable),
		defaultPrevented(false),
		phase(EventPhase::NONE),
		propagationStopped(false) {
		this->type = type;
	}

	void Event::visitFailedHandler() {
		throw std::invalid_argument("Invalid visitor.");
	}

	bool Event::getBubbles() const {
		return bubbles;
	}

	bool Event::getCancelable() const {
		return cancelable;
	}

	EventSubject * Event::getCurrentTarget() const {
		return currentTarget;
	}

	bool Event::getDefaultPrevented() const {
		return defaultPrevented;
	}

	EventPhase Event::getPhase() const {
		return phase;
	}

	EventSubject * Event::getTarget() const {
		return target;
	}

	EventType Event::getType() const {
		return type;
	}

	void Event::stopPropagation() {
		propagationStopped = true;
	}

	void Event::preventDefault() {
		if (cancelable) {
			defaultPrevented = true;
		}
	}
}