#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickConnectedEvent :
		public sf::Event::JoystickConnectEvent,
		public Event {
	public:
		JoystickConnectedEvent(sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickConnectedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
