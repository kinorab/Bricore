#include "joystickMovedListener.h"
#include "joystickMovedEvent.h"

namespace game {
	JoystickMovedListener::JoystickMovedListener(std::function<void(JoystickMovedEvent &)> callback) :
		callback(callback) {
	}

	void JoystickMovedListener::visit(JoystickMovedEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickMovedListener::getEventType() {
		return typeid(JoystickMovedEvent);
	}
}

