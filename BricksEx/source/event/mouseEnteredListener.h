#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class MouseEnteredEvent;
	class MouseEnteredListener :
		public EventListener {
	public:
		explicit MouseEnteredListener(std::function<void(MouseEnteredEvent &)> callback);
		virtual ~MouseEnteredListener() = default;
		virtual void visit(MouseEnteredEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(MouseEnteredEvent &)> callback;
	};
}
