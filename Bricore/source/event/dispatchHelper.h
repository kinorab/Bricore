#pragma once

#include "eventPhase.h"

namespace game {
	class UIEvent;
	class EventEmitter;

	class DispatchHelper {
	public:
		explicit DispatchHelper(UIEvent & event);
		virtual ~DispatchHelper() = default;
		virtual bool isPropagationStopped();
		virtual void setCurrentTarget(EventEmitter * target);
		virtual void setPhase(EventPhase phase);
		virtual void setTarget(EventEmitter * target);
	private:
		UIEvent & event;
	};
}