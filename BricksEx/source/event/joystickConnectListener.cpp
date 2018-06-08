#include "joystickConnectListener.h"

namespace game {
	JoystickConnectListener::JoystickConnectListener(std::function<void(JoystickConnectEvent &)> callback) :
		callback(callback) {
	}

	void JoystickConnectListener::visit(JoystickConnectEvent & visitable) {
		callback(visitable);
	}
}
