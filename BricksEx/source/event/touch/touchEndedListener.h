#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class TouchEndedEvent;
	class TouchEndedListener :
		public EventListener {
	public:
		explicit TouchEndedListener(std::function<void(TouchEndedEvent &)> callback);
		virtual ~TouchEndedListener() = default;
		virtual void visit(TouchEndedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(TouchEndedEvent &)> callback;
	};
}
