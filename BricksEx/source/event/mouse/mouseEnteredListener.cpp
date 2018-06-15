#include "mouseEnteredListener.h"
#include "mouseEnteredEvent.h"

namespace game {
	MouseEnteredListener::MouseEnteredListener(std::function<void(MouseEnteredEvent &)> callback) :
		callback(callback) {
	}

	void MouseEnteredListener::visit(MouseEnteredEvent & visitable) {
		callback(visitable);
	}

	std::type_index MouseEnteredListener::getEventType() {
		return typeid(MouseEnteredEvent);
	}
}
