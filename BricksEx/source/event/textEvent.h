#pragma once

#include "event.h"

namespace game {
	class TextEvent :
		public sf::Event::TextEvent,
		public Event {
	public:
		TextEvent(EventType type, sf::Event::TextEvent eventData);
		virtual ~TextEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}