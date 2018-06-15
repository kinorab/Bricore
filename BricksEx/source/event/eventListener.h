#pragma once

#include <typeindex>

namespace game {
	class EventListener {
	public:
		virtual ~EventListener() = default;
		virtual std::type_index getEventType() = 0;
	};
}
