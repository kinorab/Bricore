#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class JoystickMoveListener :
		public EventListener {
	public:
		explicit JoystickMoveListener(std::function<void(JoystickMoveEvent *)> callback);
		virtual ~JoystickMoveListener() = default;
		virtual void visit(JoystickMoveEvent * visitable) override;
	private:
		std::function<void(JoystickMoveEvent *)> callback;
	};
}
