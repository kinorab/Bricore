#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickReleasedEvent :
		public Event {
	public:
		explicit JoystickReleasedEvent(sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickReleasedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::JoystickButtonEvent released;
	};
}
