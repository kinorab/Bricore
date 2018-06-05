#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class SensorEvent :
		public sf::Event::SensorEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		SensorEvent(EventType type, sf::Event::SensorEvent eventData);
		virtual ~SensorEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}