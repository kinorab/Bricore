#include "event.h"

namespace game {
	Event::DispatchHelper::DispatchHelper(Event * event) {
		this->event = event;
	}

	void Event::DispatchHelper::setCurrentTarget(EventDispatcher * target) {
		event->currentTarget = target;
	}

	void Event::DispatchHelper::setPhase(EventPhase phase) {
		event->phase = phase;
	}

	void Event::DispatchHelper::setTarget(EventDispatcher * target) {
		event->target = target;
	}

	Event::Event(std::string type, bool bubbles, bool cancelable) :
		bubbles(bubbles),
		cancelable(cancelable),
		defaultPrevented(false),
		phase(EventPhase::NONE),
		propagationStopped(false),
		type(type) {

	}

	Event::~Event() {

	}

	bool Event::getBubbles() const {
		return bubbles;
	}

	bool Event::getCancelable() const {
		return cancelable;
	}

	EventDispatcher * Event::getCurrentTarget() const {
		return nullptr;
	}

	bool Event::getDefaultPrevented() const {
		return defaultPrevented;
	}

	EventPhase Event::getPhase() const {
		return phase;
	}

	EventDispatcher * Event::getTarget() const {
		return nullptr;
	}

	std::string Event::getType() const {
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