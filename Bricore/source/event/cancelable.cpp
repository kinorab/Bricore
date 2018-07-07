#include "cancelable.h"

namespace game {
	bool Cancelable::getDefaultPrevented() const {
		return bDefaultPrevented;
	}

	void Cancelable::preventDefault() {
		bDefaultPrevented = true;
	}
}
