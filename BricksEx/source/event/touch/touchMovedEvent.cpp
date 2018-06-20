#include "touchMovedEvent.h"
#include "touchMovedListener.h"

namespace game {
	TouchMovedEvent::TouchMovedEvent(sf::Event::TouchEvent eventData) :
		sf::Event::TouchEvent(eventData) {
	}

	void TouchMovedEvent::accept(EventListener & visitor) {
		dynamic_cast<TouchMovedListener &>(visitor).visit(*this);
	}
}
