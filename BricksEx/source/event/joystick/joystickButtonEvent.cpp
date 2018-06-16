#include "joystickButtonEvent.h"
#include "joystickButtonListener.h"

namespace game {
	JoystickButtonEvent::JoystickButtonEvent(std::type_index type, sf::Event::JoystickButtonEvent eventData) :
		UIEvent(type, false),
		sf::Event::JoystickButtonEvent(eventData) {
	}

	void JoystickButtonEvent::accept(EventListener & visitor) {
		dynamic_cast<JoystickButtonListener &>(visitor).visit(*this);
	}
}
