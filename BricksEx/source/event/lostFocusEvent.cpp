#include "lostFocusEvent.h"
#include "lostFocusListener.h"

namespace game {
	void LostFocusEvent::accept(EventListener & visitor) {
		LostFocusListener & listener = dynamic_cast<LostFocusListener &>(visitor);
		listener.visit(*this);
	}
}
