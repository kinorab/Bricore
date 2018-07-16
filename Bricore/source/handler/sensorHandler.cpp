#include "sensorHandler.h"
#include "../interact/container.h"

namespace game {
	SensorHandler::SensorHandler() noexcept {
	}

	void SensorHandler::handle(const sf::Event & event, Container & thing) {
		if (event.type == sf::Event::SensorChanged) {
			handleSensorChangedEvent(event, thing);
		}
	}

	void SensorHandler::handleSensorChangedEvent(const sf::Event & event, Container & thing) {
		thing.dispatchEvent(SensorChangedEvent(event.sensor));
	}
}