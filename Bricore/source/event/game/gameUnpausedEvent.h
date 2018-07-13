#pragma once
#include "../event.h"

namespace game {
	class GameUnpausedEvent :
		public Event {
	public:
		GameUnpausedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameUnpausedEvent() = default;
	};
}