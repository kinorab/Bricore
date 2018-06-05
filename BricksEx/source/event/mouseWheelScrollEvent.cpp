#include "mouseWheelScrollEvent.h"

namespace game {
	MouseWheelScrollEvent::MouseWheelScrollEvent(EventType type, sf::Event::MouseWheelScrollEvent eventData) :
		Event(type, true, true),
		sf::Event::MouseWheelScrollEvent(eventData) {
	}

	void MouseWheelScrollEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
