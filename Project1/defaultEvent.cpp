#include "defaultEvent.h"

namespace game {
	DefaultEvent::DispatchHelper::DispatchHelper(DefaultEvent * event) {
		this->event = event;
	}

	void DefaultEvent::DispatchHelper::setCurrentTarget(EventDispatcher * target) {
		event->currentTarget = target;
	}

	void DefaultEvent::DispatchHelper::setPhase(EventPhase phase) {
		event->phase = phase;
	}

	void DefaultEvent::DispatchHelper::setTarget(EventDispatcher * target) {
		event->target = target;
	}

	DefaultEvent::DefaultEvent(std::string type, bool bubbles, bool cancelable) :
		bubbles(bubbles),
		cancelable(cancelable),
		defaultPrevented(false),
		phase(EventPhase::NONE),
		propagationStopped(false),
		type(type) {

	}

	DefaultEvent::~DefaultEvent() {

	}

	bool DefaultEvent::getBubbles() const {
		return bubbles;
	}

	bool DefaultEvent::getCancelable() const {
		return cancelable;
	}

	EventDispatcher * DefaultEvent::getCurrentTarget() const {
		return nullptr;
	}

	bool DefaultEvent::getDefaultPrevented() const {
		return defaultPrevented;
	}

	EventPhase DefaultEvent::getPhase() const {
		return phase;
	}

	EventDispatcher * DefaultEvent::getTarget() const {
		return nullptr;
	}

	std::string DefaultEvent::getType() const {
		return type;
	}

	void DefaultEvent::stopPropagation() {
		propagationStopped = true;
	}

	void DefaultEvent::preventDefault() {
		if (cancelable) {
			defaultPrevented = true;
		}
	}
}