#include "lostFocusEvent.h"
#include "../eventListener.h"

namespace game {
	void LostFocusEvent::accept(EventListenerBase & visitor) {
        dynamic_cast<EventListener<LostFocusEvent> &>(visitor).visit(*this);
	}
}
