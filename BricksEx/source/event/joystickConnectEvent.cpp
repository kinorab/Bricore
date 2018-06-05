#include "joystickConnectEvent.h"

namespace game {
	JoystickConnectEvent::JoystickConnectEvent(EventType type, sf::Event::JoystickConnectEvent eventData) :
		Event(type, false, false),
		sf::Event::JoystickConnectEvent(eventData) {
	}

	void JoystickConnectEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
