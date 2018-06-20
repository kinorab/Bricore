#include "mouseReleasedEvent.h"
#include "mouseReleasedListener.h"

namespace game {
	MouseReleasedEvent::MouseReleasedEvent(sf::Event::MouseButtonEvent eventData) :
		sf::Event::MouseButtonEvent(eventData) {
	}

	void MouseReleasedEvent::accept(EventListener & visitor) {
		dynamic_cast<MouseReleasedListener &>(visitor).visit(*this);
	}
}
