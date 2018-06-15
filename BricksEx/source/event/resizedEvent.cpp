#include "resizedEvent.h"
#include "resizedListener.h"

namespace game {
	ResizedEvent::ResizedEvent(sf::Event::SizeEvent eventData) :
		UIEvent(typeid(ResizedEvent), false, false),
		sf::Event::SizeEvent(eventData) {
	}

	void ResizedEvent::accept(EventListener & visitor) {
		ResizedListener & listener = dynamic_cast<ResizedListener &>(visitor);
		listener.visit(*this);
	}
}
