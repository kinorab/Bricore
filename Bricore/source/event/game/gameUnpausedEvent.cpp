#include "gameUnpausedEvent.h"
#include "../eventListener.h"

namespace game {
	void GameUnpausedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameUnpausedEvent> &>(visitor).visit(*this);
	}
}
