#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GameFinishedLevelEvent :
		public Event {
	public:
		explicit GameFinishedLevelEvent(const GameStateEvent::FinishedLevelEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameFinishedLevelEvent() = default;
		GameStateEvent::FinishedLevelEvent finishedLevel;
	};
}