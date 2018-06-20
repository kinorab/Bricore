#include "joystickPressedListener.h"
#include "joystickPressedEvent.h"

namespace game {
	JoystickPressedListener::JoystickPressedListener(std::function<void(JoystickPressedEvent &)> callback) :
		callback(callback) {
	}

	void JoystickPressedListener::visit(JoystickPressedEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickPressedListener::getEventType() {
		return typeid(JoystickPressedEvent);
	}
}
