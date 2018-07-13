#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchBeganEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit TouchBeganEvent(sf::Event::TouchEvent eventData);
		virtual ~TouchBeganEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::TouchEvent began;
	};
}
