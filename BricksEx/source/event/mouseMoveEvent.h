#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class MouseMoveEvent :
		public sf::Event::MouseMoveEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		MouseMoveEvent(EventType type, sf::Event::MouseMoveEvent eventData);
		virtual ~MouseMoveEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}