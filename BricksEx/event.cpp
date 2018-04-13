#include "event.h"

namespace game {
	Event::DispatchHelper::DispatchHelper(Event * event) {
		this->event = event;
	}

	bool Event::DispatchHelper::isPropagationStopped() {
		return event->propagationStopped;
	}

	void Event::DispatchHelper::setCurrentTarget(DisplayNode * target) {
		event->currentTarget = target;
	}

	void Event::DispatchHelper::setPhase(EventPhase phase) {
		event->phase = phase;
	}

	void Event::DispatchHelper::setTarget(DisplayNode * target) {
		event->target = target;
	}

	Event::Event(sf::Event::EventType type) :
		Event(type, true, true){
	}

	Event::Event(sf::Event::EventType type, bool bubbles, bool cancelable) :
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

	DisplayNode * Event::getCurrentTarget() const {
		return currentTarget;
	}

	bool Event::getDefaultPrevented() const {
		return defaultPrevented;
	}

	EventPhase Event::getPhase() const {
		return phase;
	}

	DisplayNode * Event::getTarget() const {
		return target;
	}

	sf::Event::EventType Event::getType() const {
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