#include "keyPressedListener.h"
#include "keyPressedEvent.h"

namespace game {
	KeyPressedListener::KeyPressedListener(std::function<void(KeyPressedEvent &)> callback) :
		callback(callback) {
	}

	void KeyPressedListener::visit(KeyPressedEvent & visitable) {
		callback(visitable);
	}

	std::type_index KeyPressedListener::getEventType() {
		return typeid(KeyPressedEvent);
	}
}
