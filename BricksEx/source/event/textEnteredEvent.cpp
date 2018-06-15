#include "textEnteredEvent.h"
#include "textEnteredListener.h"

namespace game {
	TextEnteredEvent::TextEnteredEvent(sf::Event::TextEvent eventData) :
		UIEvent(typeid(TextEnteredEvent), true, true),
		sf::Event::TextEvent(eventData) {
	}

	void TextEnteredEvent::accept(EventListener & visitor) {
		TextEnteredListener & listener = dynamic_cast<TextEnteredListener &>(visitor);
		listener.visit(*this);
	}
}
