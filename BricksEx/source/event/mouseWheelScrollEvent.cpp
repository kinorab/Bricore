#include "mouseWheelScrollEvent.h"
#include "mouseWheelScrollListener.h"

namespace game {
	MouseWheelScrollEvent::MouseWheelScrollEvent(EventType type, sf::Event::MouseWheelScrollEvent eventData) :
		Event(type, true, true),
		sf::Event::MouseWheelScrollEvent(eventData) {
	}

	void MouseWheelScrollEvent::accept(EventListener & visitor) {
		MouseWheelScrollListener & listener = dynamic_cast<MouseWheelScrollListener &>(visitor);
		listener.visit(*this);
	}
}
