#pragma once
#include "../event/game/gameEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class GameHandler {
	public:
		explicit GameHandler() noexcept;
		void handler(const sf::Event & event, Container & thing);
		virtual ~GameHandler() = default;

	private:
		void handleGamePaused(const sf::Event & event, Container & thing);
		void handleGameStarted(const sf::Event & event, Container & thing);
		void handleGameUnpaused(const sf::Event & event, Container & thing);
	};
}