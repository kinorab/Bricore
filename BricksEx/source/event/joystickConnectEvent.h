#pragma once

#include "event.h"

namespace game {
	class JoystickConnectEvent :
		public sf::Event::JoystickConnectEvent,
		public Event {
	public:
		JoystickConnectEvent(EventType type, sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickConnectEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}
