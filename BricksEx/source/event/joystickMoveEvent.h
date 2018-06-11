#pragma once

#include "UIEvent.h"

namespace game {
	class JoystickMoveEvent :
		public sf::Event::JoystickMoveEvent,
		public UIEvent {
	public:
		JoystickMoveEvent(EventType type, sf::Event::JoystickMoveEvent eventData);
		virtual ~JoystickMoveEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}