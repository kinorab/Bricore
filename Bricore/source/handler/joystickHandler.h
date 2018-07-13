#pragma once
#include "../event/joystick/joystickEvent.h"

namespace game {
	class JoystickHandler {
	public:
		JoystickHandler();
		virtual ~JoystickHandler() = default;
	};
}