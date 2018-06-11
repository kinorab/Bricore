#pragma once

#include "UIEvent.h"

namespace game {
	class MouseButtonEvent :
		public sf::Event::MouseButtonEvent,
		public UIEvent {
	public:
		MouseButtonEvent(EventType type, sf::Event::MouseButtonEvent eventData);
		virtual ~MouseButtonEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}