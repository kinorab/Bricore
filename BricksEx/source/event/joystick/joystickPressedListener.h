#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickPressedEvent;
	class JoystickPressedListener :
		public EventListener {
	public:
		explicit JoystickPressedListener(std::function<void(JoystickPressedEvent &)> callback);
		virtual ~JoystickPressedListener() = default;
		virtual void visit(JoystickPressedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickPressedEvent &)> callback;
	};
}
