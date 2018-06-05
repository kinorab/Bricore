#include "touchListener.h"

namespace game {
	TouchListener::TouchListener(std::function<void(TouchEvent*)> callback) :
		callback(callback) {
	}

	void TouchListener::visit(TouchEvent * visitable) {
		callback(visitable);
	}
}

