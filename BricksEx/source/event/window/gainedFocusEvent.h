#pragma once

#include "../emptyEvent.h"

namespace game {
	class GainedFocusEvent :
		public EmptyEvent<GainedFocusEvent> {};
}