#pragma once

#include "event.h"

namespace game {
	class JoystickButtonEvent :
		public sf::Event::JoystickButtonEvent,
		public Event {
	public:
		JoystickButtonEvent(EventType type, sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickButtonEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}