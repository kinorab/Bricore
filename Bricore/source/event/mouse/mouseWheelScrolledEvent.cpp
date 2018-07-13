#include "mouseWheelScrolledEvent.h"
#include "../eventListener.h"

namespace game {
	MouseWheelScrolledEvent::MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData) :
		scrolled(eventData) {
	}

	void MouseWheelScrolledEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseWheelScrolledEvent> &>(visitor).visit(*this);
	}
}
