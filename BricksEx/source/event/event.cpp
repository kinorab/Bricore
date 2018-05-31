#include "event.h"

namespace game {
	Event::DispatchHelper::DispatchHelper(Event * event) {
		this->event = event;
	}

	bool Event::DispatchHelper::isPropagationStopped() {
		return event->propagationStopped;
	}

	void Event::DispatchHelper::setCurrentTarget(InteractiveObject * target) {
		event->currentTarget = target;
	}

	void Event::DispatchHelper::setPhase(EventPhase phase) {
		event->phase = phase;
	}

	void Event::DispatchHelper::setTarget(InteractiveObject * target) {
		event->target = target;
	}

	Event::Event(EventType type) :
		Event(type, true, true) {
	}

	Event::Event(EventType type, bool bubbles, bool cancelable) :
		bubbles(bubbles),
		cancelable(cancelable),
		defaultPrevented(false),
		phase(EventPhase::NONE),
		propagationStopped(false) {
		this->type = type;
	}

	Event::~Event() {

	}

	bool Event::getBubbles() const {
		return bubbles;
	}

	bool Event::getCancelable() const {
		return cancelable;
	}

	InteractiveObject * Event::getCurrentTarget() const {
		return currentTarget;
	}

	bool Event::getDefaultPrevented() const {
		return defaultPrevented;
	}

	EventPhase Event::getPhase() const {
		return phase;
	}

	InteractiveObject * Event::getTarget() const {
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