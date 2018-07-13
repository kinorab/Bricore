#include "windowResizedEvent.h"
#include "../eventListener.h"

namespace game {
	WindowResizedEvent::WindowResizedEvent(sf::Event::SizeEvent eventData) :
		resized(eventData) {
	}

	void WindowResizedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<WindowResizedEvent> &>(visitor).visit(*this);
	}
}
