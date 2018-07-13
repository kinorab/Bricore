#pragma once

#include "../Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickConnectedEvent :
		public Event {
	public:
		explicit JoystickConnectedEvent(sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickConnectedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::JoystickConnectEvent connected;
	};
}
