#include "touchBeganListener.h"
#include "touchBeganEvent.h"

namespace game {
	TouchBeganListener::TouchBeganListener(std::function<void(TouchBeganEvent &)> callback) :
		callback(callback) {
	}

	void TouchBeganListener::visit(TouchBeganEvent & visitable) {
		callback(visitable);
	}

	std::type_index TouchBeganListener::getEventType() {
		return typeid(TouchBeganEvent);
	}
}
