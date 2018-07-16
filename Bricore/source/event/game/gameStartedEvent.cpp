#include "gameStartedEvent.h"
#include "../eventListener.h"

namespace game {
	GameStartedEvent::GameStartedEvent(const GameEvent::StartedEvent eventType)
		: started(eventType) {
	}
	void GameStartedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameStartedEvent> &>(visitor).visit(*this);
	}
}