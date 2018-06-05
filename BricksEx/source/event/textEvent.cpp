#include "textEvent.h"

namespace game {
	TextEvent::TextEvent(EventType type, sf::Event::TextEvent eventData) :
		Event(type, true, true),
		sf::Event::TextEvent(eventData) {
	}

	void TextEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
