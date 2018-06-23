#include "mouseLeftEvent.h"
#include "../eventListener.h"

namespace game {
	void MouseLeftEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<MouseLeftEvent> &>(visitor).visit(*this);
	}
}
