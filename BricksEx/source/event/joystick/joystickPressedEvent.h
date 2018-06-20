#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickPressedEvent :
		public sf::Event::JoystickButtonEvent,
		public Event {
	public:
		JoystickPressedEvent(sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickPressedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
