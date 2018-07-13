#pragma once
#include "../event.h"

namespace game {
	class GameStartedEvent :
		public Event {
	public:
		GameStartedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameStartedEvent() = default;
	};
}