#include "joystickReleasedListener.h"
#include "joystickReleasedEvent.h"

namespace game {
	JoystickReleasedListener::JoystickReleasedListener(std::function<void(JoystickReleasedEvent &)> callback) :
		callback(callback) {
	}

	void JoystickReleasedListener::visit(JoystickReleasedEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickReleasedListener::getEventType() {
		return typeid(JoystickReleasedEvent);
	}
}
