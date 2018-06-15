#pragma once

#include "UIEvent.h"

namespace game {
	class MouseWheelScrolledEvent :
		public sf::Event::MouseWheelScrollEvent,
		public UIEvent {
	public:
		MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData);
		virtual ~MouseWheelScrolledEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}