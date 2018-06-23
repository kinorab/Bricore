#include "mouseLeftEvent.h"
#include "../emptyListener.h"

namespace game {
	void MouseLeftEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EmptyListener<MouseLeftEvent> &>(visitor).visit();
	}
}
