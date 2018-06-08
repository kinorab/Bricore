#include "mouseButtonEvent.h"
#include "mouseButtonListener.h"

namespace game {
	MouseButtonEvent::MouseButtonEvent(EventType type, sf::Event::MouseButtonEvent eventData) :
		Event(type, true, true),
		sf::Event::MouseButtonEvent(eventData) {
	}

	void MouseButtonEvent::accept(EventListener & visitor) {
		MouseButtonListener & listener = dynamic_cast<MouseButtonListener &>(visitor);
		listener.visit(*this);
	}
}
