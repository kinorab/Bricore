#pragma once
#include "../event/text/textEvent.h"

namespace game {
	class TextHandler {
	public:
		TextHandler() noexcept;
		virtual ~TextHandler() = default;
	};
}