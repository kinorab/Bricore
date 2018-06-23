#pragma once

#include "../event.h"

namespace game {
	class GainedFocusEvent :
		public Event {
	public:
		virtual ~GainedFocusEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}