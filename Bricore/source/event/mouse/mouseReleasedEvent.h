#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class MouseReleasedEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit MouseReleasedEvent(sf::Event::MouseButtonEvent eventData);
		virtual ~MouseReleasedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::MouseButtonEvent released;
	};
}
