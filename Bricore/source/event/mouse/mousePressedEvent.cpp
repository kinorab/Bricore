#include "mousePressedEvent.h"
#include "../eventListener.h"

namespace game {
	MousePressedEvent::MousePressedEvent(sf::Event::MouseButtonEvent eventData) :
		pressed(eventData) {
	}

	void MousePressedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MousePressedEvent> &>(visitor).visit(*this);
	}
}
