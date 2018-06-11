#pragma once

#include "UIEvent.h"

namespace game {
	class JoystickConnectEvent :
		public sf::Event::JoystickConnectEvent,
		public UIEvent {
	public:
		JoystickConnectEvent(EventType type, sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickConnectEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
