#include "textListener.h"

namespace game {
	TextListener::TextListener(std::function<void(TextEvent &)> callback) :
		callback(callback) {
	}

	void TextListener::visit(TextEvent & visitable) {
		callback(visitable);
	}
}

