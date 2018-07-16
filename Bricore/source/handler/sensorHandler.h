#pragma once
#include "../event/sensor/sensorEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class SensorHandler {
	public:
		SensorHandler() noexcept;
		void handle(const sf::Event & event, Container & thing);
		virtual ~SensorHandler() = default;
	private:
		void handleSensorChangedEvent(const sf::Event & event, Container & thing);
	};
}