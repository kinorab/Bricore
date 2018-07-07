#include "joystickMovedEvent.h"
#include "../eventListener.h"

namespace game {
	JoystickMovedEvent::JoystickMovedEvent(sf::Event::JoystickMoveEvent eventData) :
		sf::Event::JoystickMoveEvent(eventData) {
	}

	void JoystickMovedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<JoystickMovedEvent> &>(visitor).visit(*this);
	}
}

