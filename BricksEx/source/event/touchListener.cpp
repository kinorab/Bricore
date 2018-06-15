#include "touchListener.h"
#include "touchEvent.h"

namespace game {
	TouchListener::TouchListener(std::function<void(TouchEvent &)> callback) :
		callback(callback) {
	}

	void TouchListener::visit(TouchEvent & visitable) {
		callback(visitable);
	}

	std::type_index TouchListener::getEventType() {
		return typeid(TouchEvent);
	}
}

