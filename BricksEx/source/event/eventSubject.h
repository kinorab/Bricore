#pragma once

#include "eventType.h"
#include "eventListener.h"
#include <map>
#include <functional>

namespace game {
	class Event;

	class EventSubject {
	public:
		EventSubject();
		virtual ~EventSubject() = default;
		virtual int addListener(EventType eventType, std::shared_ptr<EventListener> listener);
		virtual void dispatchEvent(Event * event);
		virtual void removeListener(int id);
	private:
		std::map<int, std::pair<EventType, std::shared_ptr<EventListener>>> listeners;
		int idCount;
	};
}

