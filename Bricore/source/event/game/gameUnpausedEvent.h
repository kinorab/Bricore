#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GameUnpausedEvent :
		public Event {
	public:
		explicit GameUnpausedEvent(const GameEvent::PausedEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameUnpausedEvent() = default;
		GameEvent::PausedEvent unPaused;
	};
}