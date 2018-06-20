#include "mouseEnteredEvent.h"
#include "mouseEnteredListener.h"

namespace game {
	void MouseEnteredEvent::accept(EventListener & visitor) {
		dynamic_cast<MouseEnteredListener &>(visitor).visit(*this);
	}
}
