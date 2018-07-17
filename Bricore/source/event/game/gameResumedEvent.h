#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GameResumedEvent :
		public Event {
	public:
		explicit GameResumedEvent(const GameStateEvent::ResumedEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameResumedEvent() = default;
		GameStateEvent::ResumedEvent resumed;
	};
}