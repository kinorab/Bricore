#include "joystickDisconnectedListener.h"
#include "joystickDisconnectedEvent.h"

namespace game {
	JoystickDisconnectedListener::JoystickDisconnectedListener(std::function<void(JoystickDisconnectedEvent &)> callback) :
		callback(callback) {
	}

	void JoystickDisconnectedListener::visit(JoystickDisconnectedEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickDisconnectedListener::getEventType() {
		return typeid(JoystickDisconnectedEvent);
	}
}
