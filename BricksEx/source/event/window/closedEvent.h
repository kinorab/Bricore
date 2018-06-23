#pragma once

#include "../emptyEvent.h"

namespace game {
	class ClosedEvent :
		public EmptyEvent<ClosedEvent> {};
}