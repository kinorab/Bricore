#include "keyListener.h"

namespace game {
	KeyListener::KeyListener(std::function<void(KeyEvent*)> callback) :
		callback(callback) {
	}

	void KeyListener::visit(KeyEvent * visitable) {
		callback(visitable);
	}
}
