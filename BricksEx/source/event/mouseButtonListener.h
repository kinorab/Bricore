#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class MouseButtonEvent;
	class MouseButtonListener :
		public EventListener {
	public:
		explicit MouseButtonListener(std::function<void(MouseButtonEvent &)> callback);
		virtual ~MouseButtonListener() = default;
		virtual void visit(MouseButtonEvent & visitable);
	private:
		std::function<void(MouseButtonEvent &)> callback;
	};
}
