#include "mouseInSightEvent.h"
#include "../eventListener.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
	MouseInSightEvent::MouseInSightEvent(const std::shared_ptr<const sf::RenderWindow>& window)
		: inSight(sf::Mouse::getPosition(*window)) {
	}

	void MouseInSightEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<MouseInSightEvent> &>(visitor).visit(*this);
	}
}