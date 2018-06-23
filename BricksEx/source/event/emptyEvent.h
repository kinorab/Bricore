#pragma once

#include "event.h"
#include "emptyListener.h"

namespace game {
	template<typename Type>
	class EmptyEvent :
		public Event {
	public:
		virtual ~EmptyEvent() = default;
		virtual void accept(EventListenerBase & visitor) override {
			dynamic_cast<EmptyListener<Type> &>(visitor).visit();
		}
	};
}