#include "dispatchHelper.h"
#include "UIEvent.h"

namespace game {
	DispatchHelper::DispatchHelper(UIEvent & event) :
		event(event) {
	}

	bool DispatchHelper::isPropagationStopped() {
		return event.bPropagationStopped;
	}

	void DispatchHelper::setCurrentTarget(EventEmitter * target) {
		event.currentTarget = target;
	}

	void DispatchHelper::setPhase(EventPhase phase) {
		event.phase = phase;
	}

	void DispatchHelper::setTarget(EventEmitter * target) {
		event.target = target;
	}
}