#pragma once

#include "event.h"

namespace game {
	class EventDispatcher {
	public:
		virtual ~EventDispatcher() {}
		virtual void addEventListener() = 0;
		virtual bool dispatchEvent(Event * event) = 0;
		virtual bool hasEventListener() const = 0;
		virtual void removeEventListener() = 0;
	};
}
