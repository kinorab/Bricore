#include "joystickButtonEvent.h"

namespace game {
	JoystickButtonEvent::JoystickButtonEvent(EventType type, sf::Event::JoystickButtonEvent eventData) :
		Event(type, false, false),
		sf::Event::JoystickButtonEvent(eventData) {
	}

	void JoystickButtonEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
