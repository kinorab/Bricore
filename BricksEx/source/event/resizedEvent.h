#pragma once

#include "Event.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class ResizedEvent :
		public sf::Event::SizeEvent,
		public Event {
	public:
		ResizedEvent(sf::Event::SizeEvent eventData);
		virtual ~ResizedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}