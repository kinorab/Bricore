#include "joystickMoveEvent.h"
#include "joystickMoveListener.h"

namespace game {
	JoystickMoveEvent::JoystickMoveEvent(EventType type, sf::Event::JoystickMoveEvent eventData) :
		UIEvent(type, false, false),
		sf::Event::JoystickMoveEvent(eventData) {
	}

	void JoystickMoveEvent::accept(EventListener & visitor) {
		JoystickMoveListener & listener = dynamic_cast<JoystickMoveListener &>(visitor);
		listener.visit(*this);
	}
}

