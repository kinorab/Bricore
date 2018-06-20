#include "keyPressedEvent.h"
#include "keyPressedListener.h"

namespace game {
	KeyPressedEvent::KeyPressedEvent(sf::Event::KeyEvent eventData) :
		sf::Event::KeyEvent(eventData) {
	}

	void KeyPressedEvent::accept(EventListener & visitor) {
		dynamic_cast<KeyPressedListener &>(visitor).visit(*this);
	}
}
