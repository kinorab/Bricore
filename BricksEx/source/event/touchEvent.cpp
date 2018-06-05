#include "touchEvent.h"

namespace game {
	TouchEvent::TouchEvent(EventType type, sf::Event::TouchEvent eventData) :
		Event(type, true, true),
		sf::Event::TouchEvent(eventData) {
	}

	void TouchEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
