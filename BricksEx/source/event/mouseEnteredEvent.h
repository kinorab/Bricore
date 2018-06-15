#pragma once

#include "Event.h"

namespace game {
	class MouseEnteredEvent :
		public Event {
	public:
		MouseEnteredEvent() = default;
		virtual ~MouseEnteredEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
