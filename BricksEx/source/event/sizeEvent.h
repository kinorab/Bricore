#pragma once

#include "event.h"

namespace game {
	class SizeEvent :
		public sf::Event::SizeEvent,
		public Event {
	public:
		SizeEvent(EventType type, sf::Event::SizeEvent eventData);
		virtual ~SizeEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}