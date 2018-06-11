#include "touchEvent.h"
#include "touchListener.h"

namespace game {
	TouchEvent::TouchEvent(EventType type, sf::Event::TouchEvent eventData) :
		UIEvent(type, true, true),
		sf::Event::TouchEvent(eventData) {
	}

	void TouchEvent::accept(EventListener & visitor) {
		TouchListener & listener = dynamic_cast<TouchListener &>(visitor);
		listener.visit(*this);
	}
}
