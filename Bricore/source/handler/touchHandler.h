#pragma once
#include "../event/touch/touchEvent.h"

namespace game {
	class TouchHandler {
	public:
		TouchHandler() noexcept;
		virtual ~TouchHandler() = default;
	};
}