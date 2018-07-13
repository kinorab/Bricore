#include "touchBeganEvent.h"
#include "../eventListener.h"

namespace game {
	TouchBeganEvent::TouchBeganEvent(sf::Event::TouchEvent eventData) :
		began(eventData) {
	}

	void TouchBeganEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<TouchBeganEvent> &>(visitor).visit(*this);
	}
}
