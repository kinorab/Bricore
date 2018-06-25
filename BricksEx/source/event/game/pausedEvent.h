#pragma once

#include "../emptyEvent.h"

namespace game {
	class PausedEvent :
		public EmptyEvent<PausedEvent> {};
}