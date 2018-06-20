#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchEndedEvent :
		public sf::Event::TouchEvent,
		public UIEvent,
		public Cancelable {
	public:
		TouchEndedEvent(sf::Event::TouchEvent eventData);
		virtual ~TouchEndedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
