#include "touchMovedEvent.h"
#include "../eventListener.h"

namespace game {
	TouchMovedEvent::TouchMovedEvent(sf::Event::TouchEvent eventData) :
		sf::Event::TouchEvent(eventData) {
	}

	void TouchMovedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<TouchMovedEvent> &>(visitor).visit(*this);
	}
}
