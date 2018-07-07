#include "touchEndedEvent.h"
#include "../eventListener.h"

namespace game {
	TouchEndedEvent::TouchEndedEvent(sf::Event::TouchEvent eventData) :
		sf::Event::TouchEvent(eventData) {
	}

	void TouchEndedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<TouchEndedEvent> &>(visitor).visit(*this);
	}
}
