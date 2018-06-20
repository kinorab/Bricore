#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class MouseWheelScrolledEvent;
	class MouseWheelScrolledListener :
		public EventListener {
	public:
		explicit MouseWheelScrolledListener(std::function<void(MouseWheelScrolledEvent &)> callback);
		virtual ~MouseWheelScrolledListener() = default;
		virtual void visit(MouseWheelScrolledEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(MouseWheelScrolledEvent &)> callback;
	};
}
