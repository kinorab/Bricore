#include "keyListener.h"
#include "keyEvent.h"

namespace game {
	KeyListener::KeyListener(std::function<void(KeyEvent &)> callback) :
		callback(callback) {
	}

	void KeyListener::visit(KeyEvent & visitable) {
		callback(visitable);
	}

	std::type_index KeyListener::getEventType() {
		return typeid(KeyEvent);
	}
}
