#pragma once

#include "../event.h"

namespace game {
	class ClosedEvent :
		public Event {
	public:
		virtual ~ClosedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}