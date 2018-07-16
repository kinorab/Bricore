#pragma once
#include "../event/window/windowEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class WindowHandler {
	public:
		WindowHandler() noexcept;
		void handle(const sf::Event & event, Container & thing);
		virtual ~WindowHandler() = default;
	private:
		void handleWindowClosed(const sf::Event & event, Container & thing);
		void handleWindowResized(const sf::Event & event, Container & thing);
		void handleWindowGainedFocus(const sf::Event & event, Container & thing);
		void handleWindowlostFocus(const sf::Event & event, Container & thing);
	};
}