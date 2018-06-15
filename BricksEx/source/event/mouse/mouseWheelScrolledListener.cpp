#include "mouseWheelScrolledListener.h"
#include "mouseWheelScrolledEvent.h"

namespace game {
	MouseWheelScrolledListener::MouseWheelScrolledListener(std::function<void(MouseWheelScrolledEvent &)> callback) :
		callback(callback) {
	}

	void MouseWheelScrolledListener::visit(MouseWheelScrolledEvent & visitable) {
		callback(visitable);
	}

	std::type_index MouseWheelScrolledListener::getEventType() {
		return typeid(MouseWheelScrolledEvent);
	}
}
