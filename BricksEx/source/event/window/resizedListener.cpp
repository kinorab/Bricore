#include "resizedListener.h"
#include "resizedEvent.h"

namespace game {
	ResizedListener::ResizedListener(std::function<void(ResizedEvent &)> callback) :
		callback(callback) {
	}

	void ResizedListener::visit(ResizedEvent & visitable) {
		callback(visitable);
	}

	std::type_index ResizedListener::getEventType() {
		return typeid(ResizedEvent);
	}
}

