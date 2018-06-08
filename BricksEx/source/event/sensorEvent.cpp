#include "sensorEvent.h"
#include "sensorListener.h"

namespace game {
	SensorEvent::SensorEvent(EventType type, sf::Event::SensorEvent eventData) :
		Event(type, false, false),
		sf::Event::SensorEvent(eventData) {
	}

	void SensorEvent::accept(EventListener & visitor) {
		SensorListener & listener = dynamic_cast<SensorListener &>(visitor);
		listener.visit(*this);
	}
}
