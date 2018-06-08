#include "mouseButtonListener.h"

namespace game {
	MouseButtonListener::MouseButtonListener(std::function<void(MouseButtonEvent &)> callback) :
		callback(callback) {
	}

	void MouseButtonListener::visit(MouseButtonEvent & visitable) {
		callback(visitable);
	}
}
