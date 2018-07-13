#pragma once
#include "../event.h"

namespace game {
	class WindowGainedFocusEvent :
		public Event {
	public:
		WindowGainedFocusEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~WindowGainedFocusEvent() = default;
	};
}