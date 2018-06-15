#include "keyEvent.h"
#include "keyListener.h"

namespace game {
	KeyEvent::KeyEvent(std::type_index type, sf::Event::KeyEvent eventData) :
		UIEvent(type, true, true),
		sf::Event::KeyEvent(eventData) {
	}

	void KeyEvent::accept(EventListener & visitor) {
		dynamic_cast<KeyListener &>(visitor).visit(*this);
	}
}
