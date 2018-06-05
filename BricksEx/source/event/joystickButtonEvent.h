#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickButtonEvent :
		public sf::Event::JoystickButtonEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		JoystickButtonEvent(EventType type, sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickButtonEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}