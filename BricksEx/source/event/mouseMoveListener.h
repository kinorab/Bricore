#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class MouseMoveEvent;
	class MouseMoveListener :
		public EventListener {
	public:
		explicit MouseMoveListener(std::function<void(MouseMoveEvent &)> callback);
		virtual ~MouseMoveListener() = default;
		virtual void visit(MouseMoveEvent & visitable);
	private:
		std::function<void(MouseMoveEvent &)> callback;
	};
}
