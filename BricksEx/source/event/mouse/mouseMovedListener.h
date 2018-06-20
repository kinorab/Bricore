#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class MouseMovedEvent;
	class MouseMovedListener :
		public EventListener {
	public:
		explicit MouseMovedListener(std::function<void(MouseMovedEvent &)> callback);
		virtual ~MouseMovedListener() = default;
		virtual void visit(MouseMovedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(MouseMovedEvent &)> callback;
	};
}
