#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickConnectedEvent;
	class JoystickConnectedListener :
		public EventListener {
	public:
		explicit JoystickConnectedListener(std::function<void(JoystickConnectedEvent &)> callback);
		virtual ~JoystickConnectedListener() = default;
		virtual void visit(JoystickConnectedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickConnectedEvent &)> callback;
	};
}
