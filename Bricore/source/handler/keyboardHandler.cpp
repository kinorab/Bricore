#include "keyboardHandler.h"
#include "../definition/utility.h"
#include "../interact/container.h"

namespace game {
	KeyboardHandler::KeyboardHandler() noexcept {
		for (sf::Keyboard::Key i = sf::Keyboard::Unknown;
			i < sf::Keyboard::Unknown + sf::Keyboard::KeyCount;
			i = static_cast<sf::Keyboard::Key>(i + 1)) {
			keyDown.insert({ i, false });
		}
	}

	void KeyboardHandler::handle(const sf::Event & event, Container & thing) {
		if (event.type == sf::Event::KeyPressed) {
			handleKeyPressed(event, thing);
		}
		else if (event.type == sf::Event::KeyReleased) {
			handleKeyReleased(event, thing);
		}
	}

	void KeyboardHandler::handleKeyPressed(const sf::Event & event, Container & thing) {
		if (keyDown[event.key.code]) {
			return;
		}

		keyDown[event.key.code] = true;
		thing.dispatchEvent(KeyPressedEvent(event.key));
	}

	void KeyboardHandler::handleKeyReleased(const sf::Event & event, Container & thing) {
		if (!keyDown[event.key.code]) {
			return;
		}

		keyDown[event.key.code] = false;
		thing.dispatchEvent(KeyReleasedEvent(event.key));
	}
}