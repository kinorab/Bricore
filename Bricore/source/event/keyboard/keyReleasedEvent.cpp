#include "keyReleasedEvent.h"
#include "../eventListener.h"

namespace game {
	KeyReleasedEvent::KeyReleasedEvent(sf::Event::KeyEvent eventData) :
		sf::Event::KeyEvent(eventData) {
	}

	void KeyReleasedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<KeyReleasedEvent> &>(visitor).visit(*this);
	}
}
