#pragma once

#include "../template/acyclicVisitable.h"
#include "../common.h"

namespace game {
	class EventListener;

	class Event :
		public AcyclicVisitable<EventListener> {
	public:
		virtual ~Event() = default;
	};
}