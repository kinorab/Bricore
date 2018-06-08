#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class MouseWheelScrollEvent;
	class MouseWheelScrollListener :
		public EventListener {
	public:
		explicit MouseWheelScrollListener(std::function<void(MouseWheelScrollEvent &)> callback);
		virtual ~MouseWheelScrollListener() = default;
		virtual void visit(MouseWheelScrollEvent & visitable);
	private:
		std::function<void(MouseWheelScrollEvent &)> callback;
	};
}
