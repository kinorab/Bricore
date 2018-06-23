#pragma once

#include "event.h"
#include <typeindex>
#include <functional>

namespace game {
	class EventListenerBase {
	public:
		virtual std::type_index getEventType() = 0;
		virtual ~EventListenerBase() = default;
	};

	template<typename Type>
	class EventListener :
		public EventListenerBase {
		static_assert(std::is_base_of<Event, Type>::value, "Type must derive from Event");
	public:
		explicit EventListener(std::function<void(Type &)> callback) :
			callback(callback) {
		}
		virtual ~EventListener() = default;
		virtual void visit(Type & visitable) {
			callback(visitable);
		}
		virtual std::type_index getEventType() override {
			return typeid(Type);
		}
	private:
		std::function<void(Type &)> callback;
	};
}
