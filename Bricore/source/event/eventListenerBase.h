#pragma once

#include <typeindex>

namespace game {
	class EventListenerBase {
	public:
		virtual ~EventListenerBase() = default;
		virtual std::type_index getEventType() const = 0;
	};
}