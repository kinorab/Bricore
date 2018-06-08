#include "sensorListener.h"

namespace game {
	SensorListener::SensorListener(std::function<void(SensorEvent &)> callback) :
		callback(callback) {
	}

	void SensorListener::visit(SensorEvent & visitable) {
		callback(visitable);
	}
}
