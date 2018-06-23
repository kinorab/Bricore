#pragma once

#include "../template/acyclicVisitable.h"
#include "../common.h"

namespace game {
	class EventListener;

	class EventSlot {
	public:
		EventSlot();
		virtual ~EventSlot() = default;
	};
}