#include "closedEvent.h"
#include "closedListener.h"

namespace game {
	void ClosedEvent::accept(EventListener & visitor) {
		dynamic_cast<ClosedListener &>(visitor).visit(*this);
	}
}
