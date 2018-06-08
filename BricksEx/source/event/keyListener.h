#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class KeyEvent;
	class KeyListener :
		public EventListener {
	public:
		explicit KeyListener(std::function<void(KeyEvent *)> callback);
		virtual ~KeyListener() = default;
		virtual void visit(KeyEvent * visitable);
	private:
		std::function<void(KeyEvent *)> callback;
	};
}
