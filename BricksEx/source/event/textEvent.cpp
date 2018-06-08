#include "textEvent.h"
#include "textListener.h"

namespace game {
	TextEvent::TextEvent(EventType type, sf::Event::TextEvent eventData) :
		Event(type, true, true),
		sf::Event::TextEvent(eventData) {
	}

	void TextEvent::accept(EventListener * visitor) {
		TextListener * listener = dynamic_cast<TextListener *>(visitor);
		if (listener) {
			listener->visit(this);
		}
		else {
			visitFailedHandler();
		}
	}
}
