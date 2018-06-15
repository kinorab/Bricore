#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickButtonEvent;
	class JoystickButtonListener :
		public EventListener {
	public:
		explicit JoystickButtonListener(std::function<void(JoystickButtonEvent &)> callback);
		virtual ~JoystickButtonListener() = default;
		virtual void visit(JoystickButtonEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickButtonEvent &)> callback;
	};
}
