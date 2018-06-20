#pragma once

#include "../event.h"

namespace game {
	class GainedFocusEvent :
		public Event {
	public:
		GainedFocusEvent() = default;
		virtual ~GainedFocusEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}