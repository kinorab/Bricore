#include "mouseReleasedListener.h"
#include "mouseReleasedEvent.h"

namespace game {
	MouseReleasedListener::MouseReleasedListener(std::function<void(MouseReleasedEvent &)> callback) :
		callback(callback) {
	}

	void MouseReleasedListener::visit(MouseReleasedEvent & visitable) {
		callback(visitable);
	}

	std::type_index MouseReleasedListener::getEventType() {
		return typeid(MouseReleasedEvent);
	}
}
