#include "lostFocusListener.h"
#include "lostFocusEvent.h"

namespace game {
	LostFocusListener::LostFocusListener(std::function<void(LostFocusEvent &)> callback) :
		callback(callback) {
	}

	void LostFocusListener::visit(LostFocusEvent & visitable) {
		callback(visitable);
	}

	std::type_index LostFocusListener::getEventType() {
		return typeid(LostFocusEvent);
	}
}
