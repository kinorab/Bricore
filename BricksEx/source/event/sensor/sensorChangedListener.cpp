#include "sensorChangedListener.h"
#include "sensorChangedEvent.h"

namespace game {
	SensorChangedListener::SensorChangedListener(std::function<void(SensorChangedEvent &)> callback) :
		callback(callback) {
	}

	void SensorChangedListener::visit(SensorChangedEvent & visitable) {
		callback(visitable);
	}

	std::type_index SensorChangedListener::getEventType() {
		return typeid(SensorChangedEvent);
	}
}
