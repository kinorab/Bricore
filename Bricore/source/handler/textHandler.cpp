#include "textHandler.h"
#include "../interact/container.h"

namespace game {
	TextHandler::TextHandler() noexcept{

	}

	void TextHandler::handle(const sf::Event & event, Container & thing) {
		if (event.type == sf::Event::TextEntered) {
			handleTextEntered(event, thing);
		}
	}

	void TextHandler::handleTextEntered(const sf::Event & event, Container & thing) {
		thing.emit(TextEnteredEvent(event.text));
	}
}