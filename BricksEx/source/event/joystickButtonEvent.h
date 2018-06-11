#pragma once

#include "UIEvent.h"

namespace game {
	class JoystickButtonEvent :
		public sf::Event::JoystickButtonEvent,
		public UIEvent {
	public:
		JoystickButtonEvent(EventType type, sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickButtonEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}