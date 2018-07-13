#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchMovedEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit TouchMovedEvent(sf::Event::TouchEvent eventData);
		virtual ~TouchMovedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::TouchEvent moved;
	};
}
