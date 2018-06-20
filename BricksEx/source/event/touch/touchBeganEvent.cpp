#include "touchBeganEvent.h"
#include "touchBeganListener.h"

namespace game {
	TouchBeganEvent::TouchBeganEvent(sf::Event::TouchEvent eventData) :
		sf::Event::TouchEvent(eventData) {
	}

	void TouchBeganEvent::accept(EventListener & visitor) {
		dynamic_cast<TouchBeganListener &>(visitor).visit(*this);
	}
}
