#include "gameHandler.h"
#include "../interact/container.h"

namespace game {
	GameHandler::GameHandler() noexcept {
	}

	void GameHandler::handler(GameStateEvent & event, Container & thing) {
		if (event.type == GameStateEvent::GameReady) {
			handleGameReady(event, thing);
		}
		else if (event.type == GameStateEvent::GameStarted) {
			handleGameStarted(event, thing);
		}
		else if (event.type == GameStateEvent::GamePaused) {
			handleGamePaused(event, thing);
		}
		else if (event.type == GameStateEvent::GameResumed) {
			handleGameResumed(event, thing);
		}
		else if (event.type == GameStateEvent::GameFinishedLevel) {
			handleGameFinishedLevel(event, thing);
		}
		else if (event.type == GameStateEvent::GameOver) {
			handleGameOver(event, thing);
		}
	}

	void GameHandler::handleGameOver(GameStateEvent & event, Container & thing) {
		clock.restart();
		thing.dispatchAllChildrenEvent(GameOverEvent(event.over));
	}

	void GameHandler::handleGameReady(GameStateEvent & event, Container & thing) {
		event.ready.fDurationSeconds += clock.restart().asSeconds();
		thing.dispatchAllChildrenEvent(GameReadyEvent(event.ready));
	}

	void GameHandler::handleGamePaused(GameStateEvent & event, Container & thing) {
		clock.restart();
		thing.dispatchAllChildrenEvent(GamePausedEvent(event.paused));
	}

	void GameHandler::handleGameResumed(GameStateEvent & event, Container & thing) {
		event.resumed.fCountDown -= clock.restart().asSeconds();
		thing.dispatchAllChildrenEvent(GameResumedEvent(event.resumed));
	}

	void GameHandler::handleGameStarted(GameStateEvent & event, Container & thing) {
		event.started.fDurationSeconds += clock.restart().asSeconds();
		thing.dispatchAllChildrenEvent(GameStartedEvent(event.started));
	}

	void GameHandler::handleGameFinishedLevel(GameStateEvent & event, Container & thing) {
		clock.restart();
		thing.dispatchAllChildrenEvent(GameFinishedLevelEvent(event.finishedLevel));
	}
}
