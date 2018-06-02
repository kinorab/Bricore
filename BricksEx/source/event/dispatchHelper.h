#pragma once

#include "eventPhase.h"

namespace game {
	class Event;
	class EventSubject;

	class DispatchHelper {
	public:
		explicit DispatchHelper(Event * event);
		virtual bool isPropagationStopped();
		virtual void setCurrentTarget(EventSubject * target);
		virtual void setPhase(EventPhase phase);
		virtual void setTarget(EventSubject * target);
	private:
		Event * event;
	};
}