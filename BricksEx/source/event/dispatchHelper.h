#pragma once

#include "eventPhase.h"

namespace game {
	class UIEvent;
	class EventSubject;

	class DispatchHelper {
	public:
		explicit DispatchHelper(UIEvent & event);
		virtual ~DispatchHelper() = default;
		virtual bool isPropagationStopped();
		virtual void setCurrentTarget(EventSubject * target);
		virtual void setPhase(EventPhase phase);
		virtual void setTarget(EventSubject * target);
	private:
		UIEvent & event;
	};
}