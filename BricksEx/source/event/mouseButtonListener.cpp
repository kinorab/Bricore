#include "mouseButtonListener.h"
#include "mouseButtonEvent.h"

namespace game {
	MouseButtonListener::MouseButtonListener(std::function<void(MouseButtonEvent &)> callback) :
		callback(callback) {
	}

	void MouseButtonListener::visit(MouseButtonEvent & visitable) {
		callback(visitable);
	}

	std::type_index MouseButtonListener::getEventType() {
		return typeid(MouseButtonEvent);
	}
}
