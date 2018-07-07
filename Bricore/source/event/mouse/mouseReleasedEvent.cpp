#include "mouseReleasedEvent.h"
#include "../eventListener.h"

namespace game {
	MouseReleasedEvent::MouseReleasedEvent(sf::Event::MouseButtonEvent eventData) :
		sf::Event::MouseButtonEvent(eventData) {
	}

	void MouseReleasedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseReleasedEvent> &>(visitor).visit(*this);
	}
}
