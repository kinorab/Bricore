#include "mouseWheelScrolledEvent.h"
#include "mouseWheelScrolledListener.h"

namespace game {
	MouseWheelScrolledEvent::MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData) :
		sf::Event::MouseWheelScrollEvent(eventData) {
	}

	void MouseWheelScrolledEvent::accept(EventListener & visitor) {
		dynamic_cast<MouseWheelScrolledListener &>(visitor).visit(*this);
	}
}
