#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickMovedEvent;
	class JoystickMovedListener :
		public EventListener {
	public:
		explicit JoystickMovedListener(std::function<void(JoystickMovedEvent &)> callback);
		virtual ~JoystickMovedListener() = default;
		virtual void visit(JoystickMovedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickMovedEvent &)> callback;
	};
}
