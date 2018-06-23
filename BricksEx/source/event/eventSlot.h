#pragma once

#include "eventListener.h"
#include "eventSubject.h"

namespace game {
	template<typename Type>
	class EventSlot {
	public:
		explicit EventSlot(std::function<void(Type &)> callback, EventSubject & subject) :
			eventListener(callback),
			subject(subject) {
			listenerId = subject.addListener(callback);
		}
		virtual ~EventSlot() {
			subject.removeEventListener(typeid(Type), listenerId);
		};
	private:
		int listenerId;
		EventListener<Type> eventListener;
		EventSubject & subject;
	};
}