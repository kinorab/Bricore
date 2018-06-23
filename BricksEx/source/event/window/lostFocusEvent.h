#pragma once

#include "../event.h"

namespace game {
	class LostFocusEvent :
		public Event {
	public:
		virtual ~LostFocusEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}