#include "mouseWheelScrolledEvent.h"
#include "../eventListener.h"

namespace game {
	MouseWheelScrolledEvent::MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData) :
		sf::Event::MouseWheelScrollEvent(eventData) {
	}

	void MouseWheelScrolledEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseWheelScrolledEvent> &>(visitor).visit(*this);
	}
}
