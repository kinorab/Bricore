#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class MousePressedEvent :
		public sf::Event::MouseButtonEvent,
		public UIEvent,
		public Cancelable {
	public:
		MousePressedEvent(sf::Event::MouseButtonEvent eventData);
		virtual ~MousePressedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}