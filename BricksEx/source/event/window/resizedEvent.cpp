#include "resizedEvent.h"
#include "../emptyListener.h"

namespace game {
	ResizedEvent::ResizedEvent(sf::Event::SizeEvent eventData) :
		sf::Event::SizeEvent(eventData) {
	}

	void ResizedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EmptyListener<ResizedEvent> &>(visitor).visit();
	}
}
