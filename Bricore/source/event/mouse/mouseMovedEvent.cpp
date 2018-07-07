#include "mouseMovedEvent.h"
#include "../eventListener.h"

namespace game {
	MouseMovedEvent::MouseMovedEvent(sf::Event::MouseMoveEvent eventData) :
		sf::Event::MouseMoveEvent(eventData) {
	}

	void MouseMovedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseMovedEvent> &>(visitor).visit(*this);
	}
}
