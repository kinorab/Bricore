#include "joystickDisconnectedEvent.h"
#include "joystickDisconnectedListener.h"

namespace game {
	JoystickDisconnectedEvent::JoystickDisconnectedEvent(sf::Event::JoystickConnectEvent eventData) :
		sf::Event::JoystickConnectEvent(eventData) {
	}

	void JoystickDisconnectedEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickDisconnectedListener &>(visitor).visit(*this);
	}
}
