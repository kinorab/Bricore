#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class JoystickMoveEvent;
	class JoystickMoveListener :
		public EventListener {
	public:
		explicit JoystickMoveListener(std::function<void(JoystickMoveEvent *)> callback);
		virtual ~JoystickMoveListener() = default;
		virtual void visit(JoystickMoveEvent * visitable);
	private:
		std::function<void(JoystickMoveEvent *)> callback;
	};
}
