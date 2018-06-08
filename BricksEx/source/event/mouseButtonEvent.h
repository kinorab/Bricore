#pragma once

#include "event.h"

namespace game {
	class MouseButtonEvent :
		public sf::Event::MouseButtonEvent,
		public Event {
	public:
		MouseButtonEvent(EventType type, sf::Event::MouseButtonEvent eventData);
		virtual ~MouseButtonEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}