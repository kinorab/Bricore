#include "joystickButtonListener.h"
#include "joystickButtonEvent.h"

namespace game {
	JoystickButtonListener::JoystickButtonListener(std::function<void(JoystickButtonEvent &)> callback) :
		callback(callback) {
	}

	void JoystickButtonListener::visit(JoystickButtonEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickButtonListener::getEventType() {
		return typeid(JoystickButtonEvent);
	}
}
