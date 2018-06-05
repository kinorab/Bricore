#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class TextEvent :
		public sf::Event::TextEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		TextEvent(EventType type, sf::Event::TextEvent eventData);
		virtual ~TextEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}