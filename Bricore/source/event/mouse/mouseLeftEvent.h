#pragma once

#include "../emptyEvent.h"

namespace game {
	class MouseLeftEvent :
		public EmptyEvent<MouseLeftEvent> {};
}