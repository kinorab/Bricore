#include "mouseMovedEvent.h"
#include "../eventListener.h"

namespace game {
	MouseMovedEvent::MouseMovedEvent(sf::Event::MouseMoveEvent eventData) :
		moved(eventData) {
	}

	void MouseMovedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseMovedEvent> &>(visitor).visit(*this);
	}
}
