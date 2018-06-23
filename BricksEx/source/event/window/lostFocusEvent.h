#pragma once

#include "../emptyEvent.h"

namespace game {
	class LostFocusEvent :
		public EmptyEvent<LostFocusEvent>{};
}