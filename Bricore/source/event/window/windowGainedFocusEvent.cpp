#include "windowGainedFocusEvent.h"
#include "../eventListener.h"

namespace game {
	void WindowGainedFocusEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<WindowGainedFocusEvent> &>(visitor).visit(*this);
	}
}
