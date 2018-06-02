#include "dispatchHelper.h"
#include "event.h"

namespace game {
	DispatchHelper::DispatchHelper(Event * event) {
		this->event = event;
	}

	bool DispatchHelper::isPropagationStopped() {
		return event->propagationStopped;
	}

	void DispatchHelper::setCurrentTarget(InteractiveObject * target) {
		event->currentTarget = target;
	}

	void DispatchHelper::setPhase(EventPhase phase) {
		event->phase = phase;
	}

	void DispatchHelper::setTarget(InteractiveObject * target) {
		event->target = target;
	}
}