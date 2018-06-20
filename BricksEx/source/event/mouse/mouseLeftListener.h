#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class MouseLeftEvent;
	class MouseLeftListener :
		public EventListener {
	public:
		explicit MouseLeftListener(std::function<void(MouseLeftEvent &)> callback);
		virtual ~MouseLeftListener() = default;
		virtual void visit(MouseLeftEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(MouseLeftEvent &)> callback;
	};
}
