#include "mouseButtonEvent.h"
#include "mouseButtonListener.h"

namespace game {
	MouseButtonEvent::MouseButtonEvent(std::type_index type, sf::Event::MouseButtonEvent eventData) :
		UIEvent(type, true),
		sf::Event::MouseButtonEvent(eventData) {
	}

	void MouseButtonEvent::accept(EventListener & visitor) {
		dynamic_cast<MouseButtonListener &>(visitor).visit(*this);
	}
}
