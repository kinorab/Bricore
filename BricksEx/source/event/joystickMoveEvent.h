#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickMoveEvent :
		public sf::Event::JoystickMoveEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		JoystickMoveEvent(EventType type, sf::Event::JoystickMoveEvent eventData);
		virtual ~JoystickMoveEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}