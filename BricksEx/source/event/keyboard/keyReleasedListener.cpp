#include "keyReleasedListener.h"
#include "keyReleasedEvent.h"

namespace game {
	KeyReleasedListener::KeyReleasedListener(std::function<void(KeyReleasedEvent &)> callback) :
		callback(callback) {
	}

	void KeyReleasedListener::visit(KeyReleasedEvent & visitable) {
		callback(visitable);
	}

	std::type_index KeyReleasedListener::getEventType() {
		return typeid(KeyReleasedEvent);
	}
}
