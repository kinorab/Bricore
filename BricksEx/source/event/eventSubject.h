#pragma once

#include "eventType.h"
#include <map>
#include <functional>

namespace game {
	class Event;
	class EventListener;

	class EventSubject {
	public:
		EventSubject();
		virtual ~EventSubject() = default;
		virtual int addListener(EventType eventType, std::shared_ptr<EventListener> listener);
		virtual void dispatchEvent(Event & event);
		virtual void removeListener(EventType eventType, int id);
	protected:
		std::multimap<const EventType, std::pair<const int, std::shared_ptr<EventListener>>> listeners;
	private:
		int idCount;
	};
}

