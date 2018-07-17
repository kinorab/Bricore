#include "gameReadyEvent.h"
#include "../eventListener.h"

namespace game {
	GameReadyEvent::GameReadyEvent(const GameStateEvent::ReadyEvent eventType)
		: ready(eventType) {
	}

	void GameReadyEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameReadyEvent> &>(visitor).visit(*this);
	}
}