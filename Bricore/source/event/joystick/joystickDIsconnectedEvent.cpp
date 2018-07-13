#include "joystickDisconnectedEvent.h"
#include "../eventListener.h"

namespace game {
	JoystickDisconnectedEvent::JoystickDisconnectedEvent(sf::Event::JoystickConnectEvent eventData) :
		disconnected(eventData) {
	}

	void JoystickDisconnectedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<JoystickDisconnectedEvent> &>(visitor).visit(*this);
	}
}
