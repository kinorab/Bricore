#pragma once

#include "eventPhase.h"

namespace game {
	class Event;
	class InteractiveObject;

	class DispatchHelper {
	public:
		explicit DispatchHelper(Event * event);
		virtual bool isPropagationStopped();
		virtual void setCurrentTarget(InteractiveObject * target);
		virtual void setPhase(EventPhase phase);
		virtual void setTarget(InteractiveObject * target);
	private:
		Event * event;
	};
}