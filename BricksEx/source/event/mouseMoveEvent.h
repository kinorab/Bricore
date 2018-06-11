#pragma once

#include "UIEvent.h"

namespace game {
	class MouseMoveEvent :
		public sf::Event::MouseMoveEvent,
		public UIEvent {
	public:
		MouseMoveEvent(EventType type, sf::Event::MouseMoveEvent eventData);
		virtual ~MouseMoveEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}