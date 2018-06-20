#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class MouseReleasedEvent;
	class MouseReleasedListener :
		public EventListener {
	public:
		explicit MouseReleasedListener(std::function<void(MouseReleasedEvent &)> callback);
		virtual ~MouseReleasedListener() = default;
		virtual void visit(MouseReleasedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(MouseReleasedEvent &)> callback;
	};
}
