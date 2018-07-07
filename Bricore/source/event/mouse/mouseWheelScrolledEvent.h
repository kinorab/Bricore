#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class MouseWheelScrolledEvent :
		public sf::Event::MouseWheelScrollEvent,
		public UIEvent,
		public Cancelable {
	public:
		MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData);
		virtual ~MouseWheelScrolledEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}