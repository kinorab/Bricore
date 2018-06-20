#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickDisconnectedEvent :
		public sf::Event::JoystickConnectEvent,
		public Event {
	public:
		JoystickDisconnectedEvent(sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickDisconnectedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
