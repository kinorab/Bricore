#include "mouseWheelScrollListener.h"

namespace game {
	MouseWheelScrollListener::MouseWheelScrollListener(std::function<void(MouseWheelScrollEvent &)> callback) :
		callback(callback) {
	}

	void MouseWheelScrollListener::visit(MouseWheelScrollEvent & visitable) {
		callback(visitable);
	}
}
