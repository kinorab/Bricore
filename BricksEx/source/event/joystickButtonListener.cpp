#include "joystickButtonListener.h"

namespace game {
	JoystickButtonListener::JoystickButtonListener(std::function<void(JoystickButtonEvent &)> callback) :
		callback(callback) {
	}

	void JoystickButtonListener::visit(JoystickButtonEvent & visitable) {
		callback(visitable);
	}
}
