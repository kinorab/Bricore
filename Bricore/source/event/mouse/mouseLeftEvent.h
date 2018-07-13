#pragma once
#include "../event.h"

namespace game {
	class MouseLeftEvent :
		public Event {
	public:
		MouseLeftEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~MouseLeftEvent() = default;
	};
}