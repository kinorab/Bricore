#pragma once
#include "../event/joystick/joystickEvent.h"

namespace game {
	class JoystickHandler {
	public:
		JoystickHandler() noexcept;
		virtual ~JoystickHandler() = default;
	};
}