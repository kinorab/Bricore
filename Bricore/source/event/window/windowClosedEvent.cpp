#include "windowClosedEvent.h"
#include "../eventListener.h"

namespace game {
	void WindowClosedEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<WindowClosedEvent> &>(visitor).visit(*this);
	}
}
