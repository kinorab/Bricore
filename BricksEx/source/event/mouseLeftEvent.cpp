#include "mouseLeftEvent.h"
#include "mouseLeftListener.h"

namespace game {
	void MouseLeftEvent::accept(EventListener & visitor) {
		MouseLeftListener & listener = dynamic_cast<MouseLeftListener &>(visitor);
		listener.visit(*this);
	}
}
