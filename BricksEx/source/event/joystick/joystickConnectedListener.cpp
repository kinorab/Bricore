#include "joystickConnectedListener.h"
#include "joystickConnectedEvent.h"

namespace game {
	JoystickConnectedListener::JoystickConnectedListener(std::function<void(JoystickConnectedEvent &)> callback) :
		callback(callback) {
	}

	void JoystickConnectedListener::visit(JoystickConnectedEvent & visitable) {
		callback(visitable);
	}

	std::type_index JoystickConnectedListener::getEventType() {
		return typeid(JoystickConnectedEvent);
	}
}
