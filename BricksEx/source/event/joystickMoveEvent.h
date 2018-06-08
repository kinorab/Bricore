#pragma once

#include "event.h"

namespace game {
	class JoystickMoveEvent :
		public sf::Event::JoystickMoveEvent,
		public Event {
	public:
		JoystickMoveEvent(EventType type, sf::Event::JoystickMoveEvent eventData);
		virtual ~JoystickMoveEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}