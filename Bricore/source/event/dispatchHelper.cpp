#include "dispatchHelper.h"
#include "UIEvent.h"

namespace game {
	DispatchHelper::DispatchHelper(UIEvent & event) :
		event(event) {
	}

	bool DispatchHelper::isPropagationStopped() {
		return event.bPropagationStopped;
	}

	void DispatchHelper::setCurrentTarget(EventSubject * target) {
		event.currentTarget = target;
	}

	void DispatchHelper::setPhase(EventPhase phase) {
		event.phase = phase;
	}

	void DispatchHelper::setTarget(EventSubject * target) {
		event.target = target;
	}
}