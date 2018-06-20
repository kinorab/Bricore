#include "textEnteredEvent.h"
#include "textEnteredListener.h"

namespace game {
	TextEnteredEvent::TextEnteredEvent(sf::Event::TextEvent eventData) :
		sf::Event::TextEvent(eventData) {
	}

	void TextEnteredEvent::accept(EventListener & visitor) {
		dynamic_cast<TextEnteredListener &>(visitor).visit(*this);
	}
}
