#include "keyReleasedEvent.h"
#include "keyReleasedListener.h"

namespace game {
	KeyReleasedEvent::KeyReleasedEvent(sf::Event::KeyEvent eventData) :
		sf::Event::KeyEvent(eventData) {
	}

	void KeyReleasedEvent::accept(EventListener & visitor) {
		dynamic_cast<KeyReleasedListener &>(visitor).visit(*this);
	}
}
