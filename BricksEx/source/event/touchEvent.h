#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class TouchEvent :
		public sf::Event::TouchEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		TouchEvent(EventType type, sf::Event::TouchEvent eventData);
		virtual ~TouchEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}