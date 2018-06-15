#pragma once

#include "UIEvent.h"

namespace game {
	class SensorChangedEvent :
		public sf::Event::SensorEvent,
		public UIEvent {
	public:
		SensorChangedEvent(sf::Event::SensorEvent eventData);
		virtual ~SensorChangedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}