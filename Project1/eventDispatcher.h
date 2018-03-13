#pragma once

#include "event.h"

namespace game {
	class EventDispatcher {
	public:
		EventDispatcher();
		virtual ~EventDispatcher();
		virtual void addEventListener();
		virtual bool dispatchEvent(Event * event);
		virtual bool hasEventListener() const;
		virtual void removeEventListener();
	};
}
