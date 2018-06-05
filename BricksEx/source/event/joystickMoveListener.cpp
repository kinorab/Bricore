#include "joystickMoveListener.h"

namespace game {
	JoystickMoveListener::JoystickMoveListener(std::function<void(JoystickMoveEvent*)> callback) :
		callback(callback) {
	}

	void JoystickMoveListener::visit(JoystickMoveEvent * visitable) {
		callback(visitable);
	}
}

