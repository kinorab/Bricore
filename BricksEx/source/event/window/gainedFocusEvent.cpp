#include "gainedFocusEvent.h"
#include "../emptyListener.h"

namespace game {
	void GainedFocusEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EmptyListener<GainedFocusEvent> &>(visitor).visit();
	}
}
