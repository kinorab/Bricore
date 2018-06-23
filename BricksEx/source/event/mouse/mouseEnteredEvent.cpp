#include "mouseEnteredEvent.h"
#include "../emptyListener.h"

namespace game {
	void MouseEnteredEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EmptyListener<MouseEnteredEvent> &>(visitor).visit();
	}
}
