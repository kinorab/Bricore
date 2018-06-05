#include "eventListener.h"
#include "../definition/utility.h"

namespace game {
	void EventListener::visitFailedHandler() {
		throw std::invalid_argument("No corresponding function for the event.");
	}
}