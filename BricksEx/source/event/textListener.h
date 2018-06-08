#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class TextEvent;
	class TextListener :
		public EventListener {
	public:
		explicit TextListener(std::function<void(TextEvent &)> callback);
		virtual ~TextListener() = default;
		virtual void visit(TextEvent & visitable);
	private:
		std::function<void(TextEvent &)> callback;
	};
}
