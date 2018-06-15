#include "resizedEvent.h"
#include "resizedListener.h"

namespace game {
	ResizedEvent::ResizedEvent(sf::Event::SizeEvent eventData) :
		sf::Event::SizeEvent(eventData) {
	}

	void ResizedEvent::accept(EventListener & visitor) {
		dynamic_cast<ResizedListener &>(visitor).visit(*this);
	}
}
