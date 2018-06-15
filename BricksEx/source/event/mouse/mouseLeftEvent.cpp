#include "mouseLeftEvent.h"
#include "mouseLeftListener.h"

namespace game {
	void MouseLeftEvent::accept(EventListener & visitor) {
		dynamic_cast<MouseLeftListener &>(visitor).visit(*this);
	}
}
