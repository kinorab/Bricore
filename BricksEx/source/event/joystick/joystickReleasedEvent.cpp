#include "joystickReleasedEvent.h"
#include "joystickReleasedListener.h"

namespace game {
	JoystickReleasedEvent::JoystickReleasedEvent(sf::Event::JoystickButtonEvent eventData) :
		sf::Event::JoystickButtonEvent(eventData) {
	}

	void JoystickReleasedEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickReleasedListener &>(visitor).visit(*this);
	}
}
