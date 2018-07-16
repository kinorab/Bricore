#include "gameUnpausedEvent.h"
#include "../eventListener.h"

namespace game {
	GameUnpausedEvent::GameUnpausedEvent(const GameEvent::PausedEvent eventType)
		: unPaused(eventType) {
	}
	void GameUnpausedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameUnpausedEvent> &>(visitor).visit(*this);
	}
}
