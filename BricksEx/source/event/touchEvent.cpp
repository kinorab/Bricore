#include "touchEvent.h"
#include "touchListener.h"

namespace game {
	TouchEvent::TouchEvent(std::type_index type, sf::Event::TouchEvent eventData) :
		UIEvent(type, true, true),
		sf::Event::TouchEvent(eventData) {
	}

	void TouchEvent::accept(EventListener & visitor) {
		dynamic_cast<TouchListener &>(visitor).visit(*this);
	}
}
