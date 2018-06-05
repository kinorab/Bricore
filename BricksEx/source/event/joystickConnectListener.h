#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class JoystickConnectListener :
		public EventListener {
	public:
		explicit JoystickConnectListener(std::function<void(JoystickConnectEvent *)> callback);
		virtual ~JoystickConnectListener() = default;
		virtual void visit(JoystickConnectEvent * visitable) override;
	private:
		std::function<void(JoystickConnectEvent *)> callback;
	};
}
