#include "SFMLKeyboardHandler.h"
#include "definition/utility.h"
#include "event/keyEvent.h"

namespace game {
	SFMLKeyboardHandler::SFMLKeyboardHandler() {
		for (sf::Keyboard::Key i = sf::Keyboard::Unknown;
			i < sf::Keyboard::Unknown + sf::Keyboard::KeyCount;
			i = static_cast<sf::Keyboard::Key>(i + 1)) {
			keyDown.insert({ i, false });
		}
	}

	void SFMLKeyboardHandler::handle(const sf::Event & event, Container & root) {
		if (event.type == sf::Event::KeyPressed) {
			handleKeyPressed(event, root);
		}
		else if (event.type == sf::Event::KeyReleased) {
			handleKeyReleased(event, root);
		}
	}

	void SFMLKeyboardHandler::handleKeyPressed(const sf::Event & event, Container & root) {
		if (keyDown[event.key.code]) {
			return;
		}

		keyDown[event.key.code] = true;
		KeyEvent gameEvent(typeid(game::KeyEvent::Pressed), event.key);
		root.dispatchEvent(gameEvent);
	}

	void SFMLKeyboardHandler::handleKeyReleased(const sf::Event & event, Container & root) {
		if (!keyDown[event.key.code]) {
			return;
		}

		keyDown[event.key.code] = false;
		KeyEvent gameEvent(typeid(game::KeyEvent::Released), event.key);
		root.dispatchEvent(gameEvent);
	}
}