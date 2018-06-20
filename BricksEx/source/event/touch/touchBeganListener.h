#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class TouchBeganEvent;
	class TouchBeganListener :
		public EventListener {
	public:
		explicit TouchBeganListener(std::function<void(TouchBeganEvent &)> callback);
		virtual ~TouchBeganListener() = default;
		virtual void visit(TouchBeganEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(TouchBeganEvent &)> callback;
	};
}
