#include "gameHandler.h"
#include "../interact/container.h"

namespace game {
	GameHandler::GameHandler() noexcept {
	}

	void GameHandler::handler(const sf::Event & event, Container & thing) {
	}

	void GameHandler::handleGamePaused(const sf::Event & event, Container & thing) {
	}

	void GameHandler::handleGameStarted(const sf::Event & event, Container & thing) {
	}

	void GameHandler::handleGameUnpaused(const sf::Event & event, Container & thing) {
	}
}
