#pragma once

#include "eventListenerBase.h"
#include "event.h"
#include <functional>

namespace game {
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
		virtual std::type_index getEventType() const override {
			return typeid(Type);
		}
	private:
		std::function<void(Type &)> callback;
	};
}
