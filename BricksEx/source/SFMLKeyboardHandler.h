#pragma once

#include "interact/container.h"
#include <SFML/Window/Event.hpp>

namespace game {
	class SFMLKeyboardHandler {
	public:
		SFMLKeyboardHandler();
		virtual ~SFMLKeyboardHandler() = default;
		virtual void handle(const sf::Event & event, game::Container & root);
	private:
		virtual void handleKeyPressed(const sf::Event & event, game::Container & root);
		virtual void handleKeyReleased(const sf::Event & event, game::Container & root);
		std::map<const sf::Keyboard::Key, bool> keyDown;
	};
}
