#include "closedListener.h"
#include "closedEvent.h"

namespace game {
	ClosedListener::ClosedListener(std::function<void(ClosedEvent &)> callback) :
		callback(callback) {
	}

	void ClosedListener::visit(ClosedEvent & visitable) {
		callback(visitable);
	}

	std::type_index ClosedListener::getEventType() {
		return typeid(ClosedEvent);
	}
}
