#pragma once

#include "UIEvent.h"

namespace game {
	class SensorEvent :
		public sf::Event::SensorEvent,
		public UIEvent {
	public:
		SensorEvent(EventType type, sf::Event::SensorEvent eventData);
		virtual ~SensorEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}