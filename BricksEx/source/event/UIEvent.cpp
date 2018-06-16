#include "UIEvent.h"

namespace game {
	UIEvent::UIEvent(std::type_index type, bool bubbles) :
		bubbles(bubbles),
		type(type) {
	}

	bool UIEvent::getBubbles() const {
		return bubbles;
	}

	EventSubject * UIEvent::getCurrentTarget() const {
		return currentTarget;
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
}