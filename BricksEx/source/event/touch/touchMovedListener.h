#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class TouchMovedEvent;
	class TouchMovedListener :
		public EventListener {
	public:
		explicit TouchMovedListener(std::function<void(TouchMovedEvent &)> callback);
		virtual ~TouchMovedListener() = default;
		virtual void visit(TouchMovedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(TouchMovedEvent &)> callback;
	};
}
