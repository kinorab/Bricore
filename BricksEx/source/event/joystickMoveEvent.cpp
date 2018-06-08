#include "joystickMoveEvent.h"
#include "joystickMoveListener.h"

namespace game {
	JoystickMoveEvent::JoystickMoveEvent(EventType type, sf::Event::JoystickMoveEvent eventData) :
		Event(type, false, false),
		sf::Event::JoystickMoveEvent(eventData) {
	}

	void JoystickMoveEvent::accept(EventListener * visitor) {
		JoystickMoveListener * listener = dynamic_cast<JoystickMoveListener *>(visitor);
		if (listener) {
			listener->visit(this);
		}
		else {
			visitFailedHandler();
		}
	}
}

