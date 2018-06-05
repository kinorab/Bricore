#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class SizeEvent :
		public sf::Event::SizeEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		SizeEvent(EventType type, sf::Event::SizeEvent eventData);
		virtual ~SizeEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}