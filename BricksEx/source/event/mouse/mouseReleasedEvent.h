#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class MouseReleasedEvent :
		public sf::Event::MouseButtonEvent,
		public UIEvent,
		public Cancelable {
	public:
		MouseReleasedEvent(sf::Event::MouseButtonEvent eventData);
		virtual ~MouseReleasedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
