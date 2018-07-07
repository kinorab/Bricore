#include "UIEvent.h"

namespace game {
	EventSubject * UIEvent::getCurrentTarget() const {
		return currentTarget;
	}

	EventPhase UIEvent::getPhase() const {
		return phase;
	}

	EventSubject * UIEvent::getTarget() const {
		return target;
	}

	void UIEvent::stopPropagation() {
		bPropagationStopped = true;
	}
}