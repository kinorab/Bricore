#include "keyPressedEvent.h"
#include "../eventListener.h"

namespace game {
	KeyPressedEvent::KeyPressedEvent(sf::Event::KeyEvent eventData) :
		pressed(eventData) {
	}

	void KeyPressedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<KeyPressedEvent> &>(visitor).visit(*this);
	}
}
