#include "windowHandler.h"
#include "../interact/container.h"

namespace game {
	WindowHandler::WindowHandler() noexcept {
	}

	void WindowHandler::handle(const sf::Event & event, Container & thing) {
		if (event.type == sf::Event::Closed) {
			handleWindowClosed(event, thing);
		}
		else if (event.type == sf::Event::Resized) {
			handleWindowResized(event, thing);
		}
		else if (event.type == sf::Event::GainedFocus) {
			handleWindowGainedFocus(event, thing);
		}
		else if (event.type == sf::Event::LostFocus) {
			handleWindowlostFocus(event, thing);
		}
	}

	void WindowHandler::handleWindowClosed(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(WindowClosedEvent());
	}

	void WindowHandler::handleWindowResized(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(WindowResizedEvent(event.size));
	}

	void WindowHandler::handleWindowGainedFocus(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(WindowGainedFocusEvent());
	}

	void WindowHandler::handleWindowlostFocus(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(WindowLostFocusEvent());
	}
}