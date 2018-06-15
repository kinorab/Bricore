#include "joystickMovedEvent.h"
#include "joystickMovedListener.h"

namespace game {
	JoystickMovedEvent::JoystickMovedEvent(sf::Event::JoystickMoveEvent eventData) :
		sf::Event::JoystickMoveEvent(eventData) {
	}

	void JoystickMovedEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickMovedListener &>(visitor).visit(*this);
	}
}

