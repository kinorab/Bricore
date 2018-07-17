#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GamePausedEvent : 
		public Event {
	public:
		explicit GamePausedEvent(const GameStateEvent::PausedEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GamePausedEvent() = default;
		GameStateEvent::PausedEvent paused;
	};
}