#pragma once

#include "event.h"

namespace game {
	class MouseMoveEvent :
		public sf::Event::MouseMoveEvent,
		public Event {
	public:
		MouseMoveEvent(EventType type, sf::Event::MouseMoveEvent eventData);
		virtual ~MouseMoveEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}