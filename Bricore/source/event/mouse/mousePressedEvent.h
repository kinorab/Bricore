#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class MousePressedEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit MousePressedEvent(sf::Event::MouseButtonEvent eventData);
		virtual ~MousePressedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::MouseButtonEvent pressed;
	};
}