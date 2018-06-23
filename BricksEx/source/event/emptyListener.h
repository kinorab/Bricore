#pragma once

#include "eventListenerBase.h"
#include "event.h"
#include <functional>

namespace game {
	template<typename Type>
	class EmptyListener :
		public EventListenerBase {
		static_assert(std::is_base_of<Event, Type>::value, "Type must derive from Event");
	public:
		explicit EmptyListener(std::function<void(void)> callback) :
			callback(callback) {
		}
		virtual ~EmptyListener() = default;
		virtual void visit() {
			callback();
		}
		virtual std::type_index getEventType() const override {
			return typeid(Type);
		}
	private:
		std::function<void(void)> callback;
	};
}
