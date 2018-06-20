#include "mousePressedEvent.h"
#include "mousePressedListener.h"

namespace game {
	MousePressedEvent::MousePressedEvent(sf::Event::MouseButtonEvent eventData) :
		sf::Event::MouseButtonEvent(eventData) {
	}

	void MousePressedEvent::accept(EventListener & visitor) {
		dynamic_cast<MousePressedListener &>(visitor).visit(*this);
	}
}
