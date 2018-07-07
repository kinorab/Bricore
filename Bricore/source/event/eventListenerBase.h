#pragma once

#include <typeindex>

namespace game {
	class EventListenerBase {
	public:
		virtual std::type_index getEventType() const = 0;
		virtual ~EventListenerBase() = default;
	};
}