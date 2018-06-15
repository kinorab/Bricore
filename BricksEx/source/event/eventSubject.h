#pragma once

#include "../common.h"
#include <map>
#include <functional>

namespace game {
	class Event;
	class EventListener;

	class EventSubject {
	public:
		EventSubject();
		virtual ~EventSubject() = default;
		virtual int addListener(std::shared_ptr<EventListener> listener);
		virtual void dispatchEvent(Event & event);
		virtual void removeListener(std::type_index eventType, int id);
	protected:
		std::multimap<const std::type_index, std::pair<const int, std::shared_ptr<EventListener>>> listeners;
		int idCount;
	};
}

