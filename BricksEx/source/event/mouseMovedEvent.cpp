#include "mouseMovedEvent.h"
#include "mouseMovedListener.h"

namespace game {
	MouseMovedEvent::MouseMovedEvent(sf::Event::MouseMoveEvent eventData) :
		UIEvent(typeid(MouseMovedEvent), true, true),
		sf::Event::MouseMoveEvent(eventData) {
	}

	void MouseMovedEvent::accept(EventListener & visitor) {
		dynamic_cast<MouseMovedListener &>(visitor).visit(*this);
	}
}
