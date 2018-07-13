#include "sensorChangedEvent.h"
#include "../eventListener.h"

namespace game {
	SensorChangedEvent::SensorChangedEvent(sf::Event::SensorEvent eventData) :
		changed(eventData) {
	}

	void SensorChangedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<SensorChangedEvent> &>(visitor).visit(*this);
	}
}
