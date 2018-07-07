#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class MouseMovedEvent :
		public sf::Event::MouseMoveEvent,
		public UIEvent,
		public Cancelable {
	public:
		MouseMovedEvent(sf::Event::MouseMoveEvent eventData);
		virtual ~MouseMovedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}