#pragma once

#include "UIEvent.h"

namespace game {
	class JoystickConnectEvent :
		public sf::Event::JoystickConnectEvent,
		public UIEvent {
	public:
		JoystickConnectEvent(std::type_index type, sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickConnectEvent() = default;
		virtual void accept(EventListener & visitor) override;
		class Connected {};
		class Disconnected {};
	};
}
