#include "gamePausedEvent.h"
#include "../eventListener.h"

namespace game {
	void GamePausedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GamePausedEvent> &>(visitor).visit(*this);
	}
}
