#include "gameFinishedLevelEvent.h"
#include "../eventListener.h"

namespace game {
	GameFinishedLevelEvent::GameFinishedLevelEvent(const GameStateEvent::FinishedLevelEvent eventType)
		: finishedLevel(eventType) {
	}
	void GameFinishedLevelEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<GameFinishedLevelEvent> &>(visitor).visit(*this);
	}
}
