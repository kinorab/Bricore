#pragma once

#include "event.h"

namespace game {
	class MouseWheelScrollEvent :
		public sf::Event::MouseWheelScrollEvent,
		public Event {
	public:
		MouseWheelScrollEvent(EventType type, sf::Event::MouseWheelScrollEvent eventData);
		virtual ~MouseWheelScrollEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}