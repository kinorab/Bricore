#include "gainedFocusListener.h"
#include "gainedFocusEvent.h"

namespace game {
	GainedFocusListener::GainedFocusListener(std::function<void(GainedFocusEvent &)> callback) :
		callback(callback) {
	}

	void GainedFocusListener::visit(GainedFocusEvent & visitable) {
		callback(visitable);
	}

	std::type_index GainedFocusListener::getEventType() {
		return typeid(GainedFocusEvent);
	}
}
