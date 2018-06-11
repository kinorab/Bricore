#pragma once

#include "UIEvent.h"

namespace game {
	class MouseWheelScrollEvent :
		public sf::Event::MouseWheelScrollEvent,
		public UIEvent {
	public:
		MouseWheelScrollEvent(EventType type, sf::Event::MouseWheelScrollEvent eventData);
		virtual ~MouseWheelScrollEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}