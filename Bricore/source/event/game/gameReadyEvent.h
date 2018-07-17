#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GameReadyEvent :
		public Event {
	public:
		explicit GameReadyEvent(const GameStateEvent::ReadyEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameReadyEvent() = default;
		GameStateEvent::ReadyEvent ready;
	};
}