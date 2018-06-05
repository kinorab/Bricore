#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class MouseButtonEvent :
		public sf::Event::MouseButtonEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		MouseButtonEvent(EventType type, sf::Event::MouseButtonEvent eventData);
		virtual ~MouseButtonEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}