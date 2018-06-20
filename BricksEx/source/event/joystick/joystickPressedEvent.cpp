#include "joystickPressedEvent.h"
#include "joystickPressedListener.h"

namespace game {
	JoystickPressedEvent::JoystickPressedEvent(sf::Event::JoystickButtonEvent eventData) :
		sf::Event::JoystickButtonEvent(eventData) {
	}

	void JoystickPressedEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickPressedListener &>(visitor).visit(*this);
	}
}
