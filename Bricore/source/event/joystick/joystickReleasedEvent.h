#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickReleasedEvent :
		public sf::Event::JoystickButtonEvent,
		public Event {
	public:
		JoystickReleasedEvent(sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickReleasedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
