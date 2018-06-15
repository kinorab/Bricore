#include "lostFocusEvent.h"
#include "lostFocusListener.h"

namespace game {
	void LostFocusEvent::accept(EventListener & visitor) {
		dynamic_cast<LostFocusListener &>(visitor).visit(*this);
	}
}
