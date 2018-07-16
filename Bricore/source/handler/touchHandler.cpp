#include "touchHandler.h"
#include "../interact/container.h"

namespace game {
	TouchHandler::TouchHandler() noexcept {
	}

	void TouchHandler::handle(const sf::Event & event, Container & thing) {
		if (event.type == sf::Event::TouchBegan) {
			handleTouchBegan(event, thing);
		}
		else if (event.type == sf::Event::TouchMoved) {
			handleTouchMoved(event, thing);
		}
		else if (event.type == sf::Event::TouchMoved) {
			handleTouchEnded(event, thing);
		}
	}

	void TouchHandler::handleTouchBegan(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(TouchBeganEvent(event.touch));
	}

	void TouchHandler::handleTouchMoved(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(TouchMovedEvent(event.touch));
	}

	void TouchHandler::handleTouchEnded(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(TouchEndedEvent(event.touch));
	}
}