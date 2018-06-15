#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class LostFocusEvent;
	class LostFocusListener :
		public EventListener {
	public:
		explicit LostFocusListener(std::function<void(LostFocusEvent &)> callback);
		virtual ~LostFocusListener() = default;
		virtual void visit(LostFocusEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(LostFocusEvent &)> callback;
	};
}
