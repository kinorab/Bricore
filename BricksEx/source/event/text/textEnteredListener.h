#pragma once

#include "../eventListener.h"
#include <functional>

namespace game {
	class TextEnteredEvent;
	class TextEnteredListener :
		public EventListener {
	public:
		explicit TextEnteredListener(std::function<void(TextEnteredEvent &)> callback);
		virtual ~TextEnteredListener() = default;
		virtual void visit(TextEnteredEvent & visitable);
		virtual std::type_index getEventType() override;
	private:
		std::function<void(TextEnteredEvent &)> callback;
	};
}
