#pragma once
#include "../event.h"
#include <SFML/Window/Event.hpp>

namespace game {
	class SensorChangedEvent :
		public Event {
	public:
		explicit SensorChangedEvent(sf::Event::SensorEvent eventData);
		virtual ~SensorChangedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::SensorEvent changed;
	};
}