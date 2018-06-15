#include "joystickConnectEvent.h"
#include "joystickConnectListener.h"

namespace game {
	JoystickConnectEvent::JoystickConnectEvent(std::type_index type, sf::Event::JoystickConnectEvent eventData) :
		UIEvent(type, false, false),
		sf::Event::JoystickConnectEvent(eventData) {
	}

	void JoystickConnectEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickConnectListener &>(visitor).visit(*this);
	}
}
