#include "keyReleasedEvent.h"
#include "../eventListener.h"

namespace game {
	KeyReleasedEvent::KeyReleasedEvent(sf::Event::KeyEvent eventData) :
		released(eventData) {
	}

	void KeyReleasedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<KeyReleasedEvent> &>(visitor).visit(*this);
	}
}
