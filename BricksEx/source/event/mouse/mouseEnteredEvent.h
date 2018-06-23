#pragma once

#include "../event.h"

namespace game {
	class MouseEnteredEvent :
		public Event {
	public:
		MouseEnteredEvent() = default;
		virtual ~MouseEnteredEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
