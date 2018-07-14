#pragma once
#include "../event/keyboard/keyEvent.h"
#include <SFML/Window/Event.hpp>
#include <map>

namespace game {
	class Container;
	class KeyboardHandler {
	public:
		KeyboardHandler() noexcept;
		virtual ~KeyboardHandler() = default;
		virtual void handle(const sf::Event & event, Container & thing);
	private:
		virtual void handleKeyPressed(const sf::Event & event, Container & thing);
		virtual void handleKeyReleased(const sf::Event & event, Container & thing);
		std::map<sf::Keyboard::Key, bool> keyDown;
	};
}
