#include "mouseLeftListener.h"
#include "mouseLeftEvent.h"

namespace game {
	MouseLeftListener::MouseLeftListener(std::function<void(MouseLeftEvent &)> callback) :
		callback(callback) {
	}

	void MouseLeftListener::visit(MouseLeftEvent & visitable) {
		callback(visitable);
	}

	std::type_index MouseLeftListener::getEventType() {
		return typeid(MouseLeftEvent);
	}
}
