#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class ResizedEvent;
	class ResizedListener :
		public EventListener {
	public:
		explicit ResizedListener(std::function<void(ResizedEvent &)> callback);
		virtual ~ResizedListener() = default;
		virtual void visit(ResizedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(ResizedEvent &)> callback;
	};
}
