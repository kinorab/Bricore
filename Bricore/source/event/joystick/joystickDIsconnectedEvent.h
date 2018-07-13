#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickDisconnectedEvent :
		public Event {
	public:
		explicit JoystickDisconnectedEvent(sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickDisconnectedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::JoystickConnectEvent disconnected;
	};
}
