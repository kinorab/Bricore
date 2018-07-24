#include "UIEvent.h"

namespace game {
	EventEmitter * UIEvent::getCurrentTarget() const {
		return currentTarget;
	}

	EventPhase UIEvent::getPhase() const {
		return phase;
	}

	EventEmitter * UIEvent::getTarget() const {
		return target;
	}

	void UIEvent::stopPropagation() {
		bPropagationStopped = true;
	}
}