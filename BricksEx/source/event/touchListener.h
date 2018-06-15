#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class TouchEvent;
	class TouchListener :
		public EventListener {
	public:
		explicit TouchListener(std::function<void(TouchEvent &)> callback);
		virtual ~TouchListener() = default;
		virtual void visit(TouchEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(TouchEvent &)> callback;
	};
}
