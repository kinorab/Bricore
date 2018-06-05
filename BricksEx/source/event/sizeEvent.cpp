#include "sizeEvent.h"

namespace game {
	SizeEvent::SizeEvent(EventType type, sf::Event::SizeEvent eventData) :
		Event(type, false, false),
		sf::Event::SizeEvent(eventData) {
	}

	void SizeEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
