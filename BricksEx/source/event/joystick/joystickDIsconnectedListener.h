#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickDisconnectedEvent;
	class JoystickDisconnectedListener :
		public EventListener {
	public:
		explicit JoystickDisconnectedListener(std::function<void(JoystickDisconnectedEvent &)> callback);
		virtual ~JoystickDisconnectedListener() = default;
		virtual void visit(JoystickDisconnectedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickDisconnectedEvent &)> callback;
	};
}
