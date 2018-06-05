#include "mouseMoveEvent.h"

namespace game {
	MouseMoveEvent::MouseMoveEvent(EventType type, sf::Event::MouseMoveEvent eventData) :
		Event(type, true, true),
		sf::Event::MouseMoveEvent(eventData) {
	}

	void MouseMoveEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
