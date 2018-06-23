#include "closedEvent.h"
#include "../eventListener.h"

namespace game {
	void ClosedEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<ClosedEvent> &>(visitor).visit(*this);
	}
}
