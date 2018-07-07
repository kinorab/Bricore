#pragma once

#include "../template/acyclicVisitable.h"
#include "../common.h"

namespace game {
	class EventListenerBase;

	class Event :
		public AcyclicVisitable<EventListenerBase> {
	public:
		virtual ~Event() = default;
	};
}