#include "cancelable.h"

namespace game {
	bool Cancelable::getDefaultPrevented() const {
		return defaultPrevented;
	}

	void Cancelable::preventDefault() {
		defaultPrevented = true;
	}
}
