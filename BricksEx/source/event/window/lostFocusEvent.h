#pragma once

#include "../event.h"

namespace game {
	class LostFocusEvent :
		public Event {
	public:
		LostFocusEvent() = default;
		virtual ~LostFocusEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}