#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class KeyReleasedEvent;
	class KeyReleasedListener :
		public EventListener {
	public:
		explicit KeyReleasedListener(std::function<void(KeyReleasedEvent &)> callback);
		virtual ~KeyReleasedListener() = default;
		virtual void visit(KeyReleasedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(KeyReleasedEvent &)> callback;
	};
}
