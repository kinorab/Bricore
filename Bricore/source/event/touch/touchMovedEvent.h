#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchMovedEvent :
		public sf::Event::TouchEvent,
		public UIEvent,
		public Cancelable {
	public:
		TouchMovedEvent(sf::Event::TouchEvent eventData);
		virtual ~TouchMovedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
