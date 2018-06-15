#include "gainedFocusEvent.h"
#include "gainedFocusListener.h"

namespace game {
	void GainedFocusEvent::accept(EventListener & visitor) {
		GainedFocusListener & listener = dynamic_cast<GainedFocusListener &>(visitor);
		listener.visit(*this);
	}
}
