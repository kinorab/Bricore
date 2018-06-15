#include "UIEvent.h"

namespace game {
	UIEvent::UIEvent(std::type_index type, bool bubbles, bool cancelable) :
		bubbles(bubbles),
		cancelable(cancelable),
		defaultPrevented(false),
		phase(EventPhase::NONE),
		propagationStopped(false),
		type(type) {
	}

	bool UIEvent::getBubbles() const {
		return bubbles;
	}

	bool UIEvent::getCancelable() const {
		return cancelable;
	}

	EventSubject * UIEvent::getCurrentTarget() const {
		return currentTarget;
	}

	bool UIEvent::getDefaultPrevented() const {
		return defaultPrevented;
	}

	EventPhase UIEvent::getPhase() const {
		return phase;
	}

	EventSubject * UIEvent::getTarget() const {
		return target;
	}

	std::type_index UIEvent::getType() const {
		return type;
	}

	void UIEvent::stopPropagation() {
		propagationStopped = true;
	}

	void UIEvent::preventDefault() {
		if (cancelable) {
			defaultPrevented = true;
		}
	}
}