#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class KeyPressedEvent;
	class KeyPressedListener :
		public EventListener {
	public:
		explicit KeyPressedListener(std::function<void(KeyPressedEvent &)> callback);
		virtual ~KeyPressedListener() = default;
		virtual void visit(KeyPressedEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(KeyPressedEvent &)> callback;
	};
}
