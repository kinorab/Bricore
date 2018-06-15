#pragma once

#include "../event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickMovedEvent :
		public sf::Event::JoystickMoveEvent,
		public Event {
	public:
		JoystickMovedEvent(sf::Event::JoystickMoveEvent eventData);
		virtual ~JoystickMovedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}