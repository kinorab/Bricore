#include "gamePausedEvent.h"
#include "../eventListener.h"

namespace game {
	GamePausedEvent::GamePausedEvent(const GameStateEvent::PausedEvent eventType)
		: paused(eventType) {
	}
	void GamePausedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GamePausedEvent> &>(visitor).visit(*this);
	}
}
