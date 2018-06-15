#include "closedEvent.h"
#include "closedListener.h"

namespace game {
	void ClosedEvent::accept(EventListener & visitor) {
		ClosedListener & listener = dynamic_cast<ClosedListener &>(visitor);
		listener.visit(*this);
	}
}
