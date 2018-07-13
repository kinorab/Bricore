#pragma once

#include "../event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickMovedEvent :
		public Event {
	public:
		explicit JoystickMovedEvent(sf::Event::JoystickMoveEvent eventData);
		virtual ~JoystickMovedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::JoystickMoveEvent moved;
	};
}