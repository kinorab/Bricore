#include "keyEvent.h"

namespace game {
	KeyEvent::KeyEvent(EventType type, sf::Event::KeyEvent eventData) :
		Event(type, true, true),
		sf::Event::KeyEvent(eventData) {
	}

	void KeyEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
