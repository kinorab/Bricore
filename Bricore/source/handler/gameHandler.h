#pragma once
#include "../event/game/gameEvent.h"
#include "../definition/gameState.h"
#include <SFML/System/Clock.hpp>
#include <memory>

namespace game {
	class Container;
	class GameHandler {
	public:
		explicit GameHandler() noexcept;
		void handler(GameStateEvent & event, Container & thing);
		virtual ~GameHandler() = default;

	private:
		void handleGameOver(GameStateEvent & event, Container & thing);
		void handleGameReady(GameStateEvent & event, Container & thing);
		void handleGamePaused(GameStateEvent & event, Container & thing);
		void handleGameResumed(GameStateEvent & event, Container & thing);
		void handleGameStarted(GameStateEvent & event, Container & thing);
		void handleGameFinishedLevel(GameStateEvent & event, Container & thing);
		void handleGamePrepared(GameStateEvent & event, Container & thing);
		sf::Clock clock;
	};
}