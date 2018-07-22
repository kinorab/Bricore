#pragma once
#include "../event.h"
#include "../../definition/gameState.h"

namespace game {
	class GamePreparedEvent :
		public Event {
	public:
		explicit GamePreparedEvent(const GameStateEvent::PreparedEvent eventType);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~GamePreparedEvent() = default;
		GameStateEvent::PreparedEvent prepared;
	};
}