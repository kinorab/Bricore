#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class JoystickConnectEvent;
	class JoystickConnectListener :
		public EventListener {
	public:
		explicit JoystickConnectListener(std::function<void(JoystickConnectEvent &)> callback);
		virtual ~JoystickConnectListener() = default;
		virtual void visit(JoystickConnectEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(JoystickConnectEvent &)> callback;
	};
}
