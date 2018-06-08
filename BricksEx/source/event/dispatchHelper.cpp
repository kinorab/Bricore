#include "dispatchHelper.h"
#include "event.h"

namespace game {
	DispatchHelper::DispatchHelper(Event & event) :
		event(event) {
	}

	bool DispatchHelper::isPropagationStopped() {
		return event.propagationStopped;
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