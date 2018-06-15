#include "sensorChangedEvent.h"
#include "sensorChangedListener.h"

namespace game {
	SensorChangedEvent::SensorChangedEvent(sf::Event::SensorEvent eventData) :
		UIEvent(typeid(SensorChangedEvent), false, false),
		sf::Event::SensorEvent(eventData) {
	}

	void SensorChangedEvent::accept(EventListener & visitor) {
		SensorChangedListener & listener = dynamic_cast<SensorChangedListener &>(visitor);
		listener.visit(*this);
	}
}
