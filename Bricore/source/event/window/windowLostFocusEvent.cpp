#include "windowLostFocusEvent.h"
#include "../eventListener.h"

namespace game {
	void WindowLostFocusEvent::accept(EventListenerBase & visitor) {
		dynamic_cast<EventListener<WindowLostFocusEvent> &>(visitor).visit(*this);
	}
}
