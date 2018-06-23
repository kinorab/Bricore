#include "joystickReleasedEvent.h"
#include "../eventListener.h"

namespace game {
	JoystickReleasedEvent::JoystickReleasedEvent(sf::Event::JoystickButtonEvent eventData) :
		sf::Event::JoystickButtonEvent(eventData) {
	}

	void JoystickReleasedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<JoystickReleasedEvent> &>(visitor).visit(*this);
	}
}
