#pragma once

#include "../emptyEvent.h"

namespace game {
	class StartedEvent :
		public EmptyEvent<StartedEvent> {};
}