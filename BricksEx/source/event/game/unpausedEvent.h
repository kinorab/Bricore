#pragma once

#include "../emptyEvent.h"

namespace game {
	class UnpausedEvent :
		public EmptyEvent<UnpausedEvent> {};
}