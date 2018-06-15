#pragma once

#include "../event.h"

namespace game {
	class MouseLeftEvent :
		public Event {
	public:
		MouseLeftEvent() = default;
		virtual ~MouseLeftEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
