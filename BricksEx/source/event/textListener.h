#pragma once

#include "eventListener.h"
#include <functional>

namespace game {
	class TextListener :
		public EventListener {
	public:
		explicit TextListener(std::function<void(TextEvent *)> callback);
		virtual ~TextListener() = default;
		virtual void visit(TextEvent * visitable) override;
	private:
		std::function<void(TextEvent *)> callback;
	};
}
