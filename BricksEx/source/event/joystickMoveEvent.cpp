#include "joystickMoveEvent.h"

namespace game {
	JoystickMoveEvent::JoystickMoveEvent(EventType type, sf::Event::JoystickMoveEvent eventData) :
		Event(type, false, false),
		sf::Event::JoystickMoveEvent(eventData) {
	}

	void JoystickMoveEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}

