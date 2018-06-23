#include "gainedFocusEvent.h"
#include "../eventListener.h"

namespace game {
	void GainedFocusEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<GainedFocusEvent> &>(visitor).visit(*this);
	}
}
