#pragma once

#include "UIEvent.h"

namespace game {
	class MouseMovedEvent :
		public sf::Event::MouseMoveEvent,
		public UIEvent {
	public:
		MouseMovedEvent(sf::Event::MouseMoveEvent eventData);
		virtual ~MouseMovedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}