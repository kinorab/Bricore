#include "mouseMoveEvent.h"
#include "mouseMoveListener.h"

namespace game {
	MouseMoveEvent::MouseMoveEvent(EventType type, sf::Event::MouseMoveEvent eventData) :
		Event(type, true, true),
		sf::Event::MouseMoveEvent(eventData) {
	}

	void MouseMoveEvent::accept(EventListener * visitor) {
		MouseMoveListener * listener = dynamic_cast<MouseMoveListener *>(visitor);
		if (listener) {
			listener->visit(this);
		}
		else {
			visitFailedHandler();
		}
	}
}
