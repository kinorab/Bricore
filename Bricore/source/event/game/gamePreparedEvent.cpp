#include "gamePreparedEvent.h"
#include "../eventListener.h"

namespace game {
	GamePreparedEvent::GamePreparedEvent(const GameStateEvent::PreparedEvent eventType)
		: prepared(eventType) {
	}

	void GamePreparedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GamePreparedEvent> &>(visitor).visit(*this);
	}
}