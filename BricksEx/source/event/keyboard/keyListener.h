#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class KeyEvent;
	class KeyListener :
		public EventListener {
	public:
		explicit KeyListener(std::function<void(KeyEvent &)> callback);
		virtual ~KeyListener() = default;
		virtual void visit(KeyEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(KeyEvent &)> callback;
	};
}
