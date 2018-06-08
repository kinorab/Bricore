#include "keyEvent.h"
#include "keyListener.h"

namespace game {
	KeyEvent::KeyEvent(EventType type, sf::Event::KeyEvent eventData) :
		Event(type, true, true),
		sf::Event::KeyEvent(eventData) {
	}

	void KeyEvent::accept(EventListener * visitor) {
		KeyListener * listener = dynamic_cast<KeyListener *>(visitor);
		if (listener) {
			listener->visit(this);
		}
		else {
			visitFailedHandler();
		}
	}
}
