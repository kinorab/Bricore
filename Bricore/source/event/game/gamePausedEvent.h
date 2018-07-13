#pragma once
#include "../event.h"

namespace game {
	class GamePausedEvent : 
		public Event {
	public:
		GamePausedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GamePausedEvent() = default;
	};
}