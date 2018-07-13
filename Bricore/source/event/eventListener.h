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
			typeCallback{ true, callback }
			, voidCallback{ false, std::function<void(void)>() } {
		}
		explicit EventListener(std::function<void(void)> callback) :
			voidCallback{ true , callback }
			, typeCallback{ false, std::function<void(Type &)>() } {
		}
		void visit(Type & visitable) {
			if (typeCallback.first) {
				typeCallback.second(visitable);
				return;
			}
			else if (voidCallback.first) {
				voidCallback.second();
				return;
			}
			throw std::exception("Unexcept error.");
		}
		virtual std::type_index getEventType() const override {
			return typeid(Type);
		}
		virtual ~EventListener() = default;

	private:
		std::pair<bool, std::function<void(Type &)>> typeCallback;
		std::pair<bool, std::function<void(void)>> voidCallback;
	};
}
