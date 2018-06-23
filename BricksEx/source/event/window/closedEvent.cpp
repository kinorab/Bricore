#include "closedEvent.h"
#include "../emptyListener.h"

namespace game {
	void ClosedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EmptyListener<ClosedEvent> &>(visitor).visit();
	}
}
