#include "joystickConnectListener.h"
#include "joystickConnectEvent.h"

namespace game {
	JoystickConnectListener::JoystickConnectListener(std::function<void(JoystickConnectEvent &)> callback) :
		callback(callback) {
	}

	void JoystickConnectListener::visit(JoystickConnectEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickConnectListener::getEventType() {
		return typeid(JoystickConnectEvent);
	}
}
