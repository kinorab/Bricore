#include "mouseEnteredEvent.h"
#include "../eventListener.h"

namespace game {
	void MouseEnteredEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseEnteredEvent> &>(visitor).visit(*this);
	}
}
