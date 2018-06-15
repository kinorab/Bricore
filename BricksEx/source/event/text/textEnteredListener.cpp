#include "textEnteredListener.h"
#include "textEnteredEvent.h"

namespace game {
	TextEnteredListener::TextEnteredListener(std::function<void(TextEnteredEvent &)> callback) :
		callback(callback) {
	}

	void TextEnteredListener::visit(TextEnteredEvent & visitable) {
		callback(visitable);
	}

	std::type_index TextEnteredListener::getEventType() {
		return typeid(TextEnteredEvent);
	}
}

