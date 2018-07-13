#pragma once
#include "../event.h"

namespace game {
	class WindowLostFocusEvent :
		public Event {
	public:
		WindowLostFocusEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~WindowLostFocusEvent() = default;
	};
}