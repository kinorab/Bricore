#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickReleasedEvent;
	class JoystickReleasedListener :
		public EventListener {
	public:
		explicit JoystickReleasedListener(std::function<void(JoystickReleasedEvent &)> callback);
		virtual ~JoystickReleasedListener() = default;
		virtual void visit(JoystickReleasedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickReleasedEvent &)> callback;
	};
}
