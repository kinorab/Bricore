#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class MouseWheelScrolledEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit MouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent eventData);
		virtual ~MouseWheelScrolledEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::MouseWheelScrollEvent scrolled;
	};
}