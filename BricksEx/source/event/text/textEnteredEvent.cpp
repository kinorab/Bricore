#include "textEnteredEvent.h"
#include "textEnteredListener.h"

namespace game {
	TextEnteredEvent::TextEnteredEvent(sf::Event::TextEvent eventData) :
		UIEvent(typeid(TextEnteredEvent), true),
		sf::Event::TextEvent(eventData) {
	}

	void TextEnteredEvent::accept(EventListener & visitor) {
		dynamic_cast<TextEnteredListener &>(visitor).visit(*this);
	}
}
