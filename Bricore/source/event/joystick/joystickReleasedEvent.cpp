#include "joystickReleasedEvent.h"
#include "../eventListener.h"

namespace game {
	JoystickReleasedEvent::JoystickReleasedEvent(sf::Event::JoystickButtonEvent eventData) :
		released(eventData) {
	}

	void JoystickReleasedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<JoystickReleasedEvent> &>(visitor).visit(*this);
	}
}
