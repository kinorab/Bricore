#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class MouseWheelScrollEvent :
		public sf::Event::MouseWheelScrollEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		MouseWheelScrollEvent(EventType type, sf::Event::MouseWheelScrollEvent eventData);
		virtual ~MouseWheelScrollEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}