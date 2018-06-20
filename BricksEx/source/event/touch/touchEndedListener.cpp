#include "touchEndedListener.h"
#include "touchEndedEvent.h"

namespace game {
	TouchEndedListener::TouchEndedListener(std::function<void(TouchEndedEvent &)> callback) :
		callback(callback) {
	}

	void TouchEndedListener::visit(TouchEndedEvent & visitable) {
		callback(visitable);
	}

	std::type_index TouchEndedListener::getEventType() {
		return typeid(TouchEndedEvent);
	}
}
