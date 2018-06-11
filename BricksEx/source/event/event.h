#pragma once

#include "../template/acyclicVisitable.h"
#include "eventType.h"

namespace game {
	class EventListener;

	class Event :
		public AcyclicVisitable<EventListener> {
	public:
		virtual ~Event() = default;
		virtual EventType getType() const;
	protected:
		EventType type;
	};
}