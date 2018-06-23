#pragma once

#include "../event.h"

namespace game {
	class MouseLeftEvent :
		public Event {
	public:
		virtual ~MouseLeftEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
