#include "joystickMovedEvent.h"
#include "joystickMovedListener.h"

namespace game {
	JoystickMovedEvent::JoystickMovedEvent(sf::Event::JoystickMoveEvent eventData) :
		UIEvent(typeid(JoystickMovedEvent), false, false),
		sf::Event::JoystickMoveEvent(eventData) {
	}

	void JoystickMovedEvent::accept(EventListener & visitor) {
		JoystickMovedListener & listener = dynamic_cast<JoystickMovedListener &>(visitor);
		listener.visit(*this);
	}
}

