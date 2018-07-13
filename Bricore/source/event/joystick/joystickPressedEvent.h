#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickPressedEvent :
		public Event {
	public:
		explicit JoystickPressedEvent(sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickPressedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::JoystickButtonEvent pressed;
	};
}
