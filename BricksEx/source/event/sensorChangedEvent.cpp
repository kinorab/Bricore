#include "sensorChangedEvent.h"
#include "sensorChangedListener.h"

namespace game {
	SensorChangedEvent::SensorChangedEvent(sf::Event::SensorEvent eventData) :
		sf::Event::SensorEvent(eventData) {
	}

	void SensorChangedEvent::accept(EventListener & visitor) {
		dynamic_cast<SensorChangedListener &>(visitor).visit(*this);
	}
}
