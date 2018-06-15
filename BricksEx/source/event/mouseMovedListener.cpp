#include "mouseMovedListener.h"
#include "mouseMovedEvent.h"

namespace game {
	MouseMovedListener::MouseMovedListener(std::function<void(MouseMovedEvent &)> callback) :
		callback(callback) {
	}

	void MouseMovedListener::visit(MouseMovedEvent & visitable) {
		callback(visitable);
	}

	std::type_index MouseMovedListener::getEventType() {
		return typeid(MouseMovedEvent);
	}
}
