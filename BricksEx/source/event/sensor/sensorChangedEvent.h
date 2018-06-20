#pragma once

#include "../event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class SensorChangedEvent :
		public sf::Event::SensorEvent,
		public Event {
	public:
		SensorChangedEvent(sf::Event::SensorEvent eventData);
		virtual ~SensorChangedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}