#pragma once

#include "UIEvent.h"

namespace game {
	class JoystickMovedEvent :
		public sf::Event::JoystickMoveEvent,
		public UIEvent {
	public:
		JoystickMovedEvent(sf::Event::JoystickMoveEvent eventData);
		virtual ~JoystickMovedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}