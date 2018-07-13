#pragma once
#include "../template/acyclicVisitable.h"
#include "../common.h"

namespace game {
	class EventListenerBase;

	class Event :
		public AcyclicVisitable<EventListenerBase> {
	public:
		virtual void accept(EventListenerBase & visitor) = 0;
		virtual ~Event() = default;
	};
}