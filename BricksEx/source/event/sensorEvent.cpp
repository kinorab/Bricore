#include "sensorEvent.h"

namespace game {
	SensorEvent::SensorEvent(EventType type, sf::Event::SensorEvent eventData) :
		Event(type, false, false),
		sf::Event::SensorEvent(eventData) {
	}

	void SensorEvent::accept(EventListener * visitor) {
		visitor->visit(this);
	}
}
