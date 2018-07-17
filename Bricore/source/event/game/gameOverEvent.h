#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GameOverEvent :
		public Event {
	public:
		explicit GameOverEvent(const GameStateEvent::OverEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GameOverEvent() = default;
		GameStateEvent::OverEvent over;
	};
}