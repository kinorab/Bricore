#include "mouseMovedEvent.h"
#include "../eventListener.h"
#include "../../definition/userSystem.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace game {
	MouseMovedEvent::MouseMovedEvent(const std::shared_ptr<const sf::RenderWindow> & window)
		: moved(sf::Mouse::getPosition(*window)) {
	}

	void MouseMovedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseMovedEvent> &>(visitor).visit(*this);
	}
}
