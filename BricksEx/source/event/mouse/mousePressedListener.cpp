#include "mousePressedListener.h"
#include "mousePressedEvent.h"

namespace game {
	MousePressedListener::MousePressedListener(std::function<void(MousePressedEvent &)> callback) :
		callback(callback) {
	}

	void MousePressedListener::visit(MousePressedEvent & visitable) {
		callback(visitable);
	}

	std::type_index MousePressedListener::getEventType() {
		return typeid(MousePressedEvent);
	}
}
