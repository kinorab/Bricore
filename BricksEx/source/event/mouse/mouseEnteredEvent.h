#pragma once

#include "../emptyEvent.h"

namespace game {
	class MouseEnteredEvent :
		public EmptyEvent<MouseEnteredEvent> {};
}