#pragma once

#include "UIEvent.h"

namespace game {
	class MouseButtonEvent :
		public sf::Event::MouseButtonEvent,
		public UIEvent {
	public:
		MouseButtonEvent(std::type_index type, sf::Event::MouseButtonEvent eventData);
		virtual ~MouseButtonEvent() = default;
		virtual void accept(EventListener & visitor) override;
		class Pressed {};
		class Released {};
	};
}