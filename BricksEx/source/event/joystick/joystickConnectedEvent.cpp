#include "joystickConnectedEvent.h"
#include "../eventListener.h"

namespace game {
	JoystickConnectedEvent::JoystickConnectedEvent(sf::Event::JoystickConnectEvent eventData) :
		sf::Event::JoystickConnectEvent(eventData) {
	}

	void JoystickConnectedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<JoystickConnectedEvent> &>(visitor).visit(*this);
	}
}
