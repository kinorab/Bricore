#include "mouseMoveListener.h"

namespace game {
	MouseMoveListener::MouseMoveListener(std::function<void(MouseMoveEvent*)> callback) :
		callback(callback) {
	}

	void MouseMoveListener::visit(MouseMoveEvent * visitable) {
		callback(visitable);
	}
}
