#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchBeganEvent :
		public sf::Event::TouchEvent,
		public UIEvent,
		public Cancelable {
	public:
		TouchBeganEvent(sf::Event::TouchEvent eventData);
		virtual ~TouchBeganEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}
