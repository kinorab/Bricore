#include "joystickButtonEvent.h"
#include "joystickButtonListener.h"

namespace game {
	JoystickButtonEvent::JoystickButtonEvent(EventType type, sf::Event::JoystickButtonEvent eventData) :
		Event(type, false, false),
		sf::Event::JoystickButtonEvent(eventData) {
	}

	void JoystickButtonEvent::accept(EventListener & visitor) {
		JoystickButtonListener & listener = dynamic_cast<JoystickButtonListener &>(visitor);
		listener.visit(*this);
	}
}
