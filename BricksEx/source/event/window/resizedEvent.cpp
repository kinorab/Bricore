#include "resizedEvent.h"
#include "../eventListener.h"

namespace game {
	ResizedEvent::ResizedEvent(sf::Event::SizeEvent eventData) :
		sf::Event::SizeEvent(eventData) {
	}

	void ResizedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<ResizedEvent> &>(visitor).visit(*this);
	}
}
