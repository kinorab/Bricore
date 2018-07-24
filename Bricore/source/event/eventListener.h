#pragma once
#include "eventListenerBase.h"
#include "event.h"
#include <functional>
#include <variant>

namespace game {
	template<typename Type>
	class EventListener :
		public EventListenerBase {
		static_assert(std::is_base_of<Event, Type>::value, "Type must derive from Event");
	public:
		explicit EventListener(std::function<void(Type &)> callback) :
			callback{ callback } {
		}
		explicit EventListener(std::function<void(void)> callback) :
			callback{ callback } {
		}
		void visit(Type & visitable) {
			if (std::holds_alternative<std::function<void(Type &)>>(callback)) {
				std::get<std::function<void(Type &)>>(callback)(visitable);
			}
			else {
				std::get<std::function<void(void)>>(callback)();
			}
		}
		virtual std::type_index getEventType() const override {
			return typeid(Type);
		}
		virtual ~EventListener() = default;

	private:
		std::variant <
			std::function<void(Type &)>,
			std::function<void(void)>
		> callback;
	};
}
