#pragma once

#include "Event.h"

namespace game {
	class LostFocusEvent :
		public Event {
	public:
		LostFocusEvent() = default;
		virtual ~LostFocusEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}