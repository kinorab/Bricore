#include "gameResumedEvent.h"
#include "../eventListener.h"

namespace game {
	GameResumedEvent::GameResumedEvent(const GameStateEvent::ResumedEvent eventType)
		: resumed(eventType) {
	}

	void GameResumedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameResumedEvent> &>(visitor).visit(*this);
	}
}