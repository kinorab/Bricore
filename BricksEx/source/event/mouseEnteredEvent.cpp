#include "mouseEnteredEvent.h"
#include "mouseEnteredListener.h"

namespace game {
	void MouseEnteredEvent::accept(EventListener & visitor) {
		MouseEnteredListener & listener = dynamic_cast<MouseEnteredListener &>(visitor);
		listener.visit(*this);
	}
}
