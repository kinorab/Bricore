#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class ClosedEvent;
	class ClosedListener :
		public EventListener {
	public:
		explicit ClosedListener(std::function<void(ClosedEvent &)> callback);
		virtual ~ClosedListener() = default;
		virtual void visit(ClosedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(ClosedEvent &)> callback;
	};
}
