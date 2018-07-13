#include "touchMovedEvent.h"
#include "../eventListener.h"

namespace game {
	TouchMovedEvent::TouchMovedEvent(sf::Event::TouchEvent eventData) :
		moved(eventData) {
	}

	void TouchMovedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<TouchMovedEvent> &>(visitor).visit(*this);
	}
}
