#pragma once
#include "../event/window/windowEvent.h"

namespace game {
	class WindowHandler {
	public:
		WindowHandler() noexcept;
		virtual ~WindowHandler() = default;
	};
}