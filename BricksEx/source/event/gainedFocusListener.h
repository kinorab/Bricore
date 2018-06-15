#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class GainedFocusEvent;
	class GainedFocusListener :
		public EventListener {
	public:
		explicit GainedFocusListener(std::function<void(GainedFocusEvent &)> callback);
		virtual ~GainedFocusListener() = default;
		virtual void visit(GainedFocusEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(GainedFocusEvent &)> callback;
	};
}
