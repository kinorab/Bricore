#pragma once
#include "../event.h"

namespace game {
	class WindowClosedEvent :
		public Event {
	public:
		WindowClosedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~WindowClosedEvent() = default;
	};
}