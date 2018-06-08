#include "sizeListener.h"

namespace game {
	SizeListener::SizeListener(std::function<void(SizeEvent &)> callback) :
		callback(callback) {
	}

	void SizeListener::visit(SizeEvent & visitable) {
		callback(visitable);
	}
}

