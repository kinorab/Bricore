#include "mouseWheelScrolledEvent.h"
#include "mouseWheelScrolledListener.h"

namespace game {
	MouseWheelScrolledEvent::MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData) :
		UIEvent(typeid(MouseWheelScrolledEvent), true, true),
		sf::Event::MouseWheelScrollEvent(eventData) {
	}

	void MouseWheelScrolledEvent::accept(EventListener & visitor) {
		MouseWheelScrolledListener & listener = dynamic_cast<MouseWheelScrolledListener &>(visitor);
		listener.visit(*this);
	}
}
