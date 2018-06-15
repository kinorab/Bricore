#pragma once

#include "Event.h"

namespace game {
	class ClosedEvent :
		public Event {
	public:
		ClosedEvent() = default;
		virtual ~ClosedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}