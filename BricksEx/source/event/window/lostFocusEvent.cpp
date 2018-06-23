#include "lostFocusEvent.h"
#include "../emptyListener.h"

namespace game {
	void LostFocusEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EmptyListener<LostFocusEvent> &>(visitor).visit();
	}
}
