#include "touchEndedEvent.h"
#include "touchEndedListener.h"

namespace game {
	TouchEndedEvent::TouchEndedEvent(sf::Event::TouchEvent eventData) :
		sf::Event::TouchEvent(eventData) {
	}

	void TouchEndedEvent::accept(EventListener & visitor) {
		dynamic_cast<TouchEndedListener &>(visitor).visit(*this);
	}
}
