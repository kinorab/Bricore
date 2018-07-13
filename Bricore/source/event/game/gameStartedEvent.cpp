#include "gameStartedEvent.h"
#include "../eventListener.h"

namespace game {
	void GameStartedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameStartedEvent> &>(visitor).visit(*this);
	}
}