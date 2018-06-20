#include "joystickConnectedEvent.h"
#include "joystickConnectedListener.h"

namespace game {
	JoystickConnectedEvent::JoystickConnectedEvent(sf::Event::JoystickConnectEvent eventData) :
		sf::Event::JoystickConnectEvent(eventData) {
	}

	void JoystickConnectedEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickConnectedListener &>(visitor).visit(*this);
	}
}
