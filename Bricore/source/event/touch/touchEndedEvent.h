#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchEndedEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit TouchEndedEvent(sf::Event::TouchEvent eventData);
		virtual ~TouchEndedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::TouchEvent ended;
	};
}
