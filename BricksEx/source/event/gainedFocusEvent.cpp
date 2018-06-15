#include "gainedFocusEvent.h"
#include "gainedFocusListener.h"

namespace game {
	void GainedFocusEvent::accept(EventListener & visitor) {
		dynamic_cast<GainedFocusListener &>(visitor).visit(*this);
	}
}
