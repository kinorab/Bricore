#include "gameOverEvent.h"
#include "../eventListener.h"

namespace game {
	GameOverEvent::GameOverEvent(const GameStateEvent::OverEvent eventType) 
		: over(eventType) {
	}

	void GameOverEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameOverEvent> &>(visitor).visit(*this);
	}
}