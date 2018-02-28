#pragma once

#include "event.h"

namespace game {
	class DefaultEvent :
		public Event {
		DefaultEvent();
		virtual ~DefaultEvent() override;
	};
}