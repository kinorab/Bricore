#include "touchMovedListener.h"
#include "touchMovedEvent.h"

namespace game {
	TouchMovedListener::TouchMovedListener(std::function<void(TouchMovedEvent &)> callback) :
		callback(callback) {
	}

	void TouchMovedListener::visit(TouchMovedEvent & visitable) {
		callback(visitable);
	}

	std::type_index TouchMovedListener::getEventType() {
		return typeid(TouchMovedEvent);
	}
}
