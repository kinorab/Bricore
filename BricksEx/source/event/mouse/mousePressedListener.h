#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class MousePressedEvent;
	class MousePressedListener :
		public EventListener {
	public:
		explicit MousePressedListener(std::function<void(MousePressedEvent &)> callback);
		virtual ~MousePressedListener() = default;
		virtual void visit(MousePressedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(MousePressedEvent &)> callback;
	};
}
