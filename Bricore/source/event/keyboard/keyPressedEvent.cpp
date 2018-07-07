#include "keyPressedEvent.h"
#include "../eventListener.h"

namespace game {
	KeyPressedEvent::KeyPressedEvent(sf::Event::KeyEvent eventData) :
		sf::Event::KeyEvent(eventData) {
	}

	void KeyPressedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<KeyPressedEvent> &>(visitor).visit(*this);
	}
}
