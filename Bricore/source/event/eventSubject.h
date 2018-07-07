#pragma once

#include "../common.h"
#include <map>
#include <functional>

namespace game {
	class Event;
	class EventListenerBase;

	class EventSubject {
	public:
		virtual ~EventSubject() = default;
		virtual int addListener(std::shared_ptr<EventListenerBase> listener);
		virtual int addListener(std::shared_ptr<EventListenerBase> listener, std::weak_ptr<EventSubject> trackedSubject);
		virtual void dispatchEvent(Event & event);
		virtual void dispatchEvent(Event && event);
		virtual void removeListener(std::type_index eventType, int id);
	protected:
		EventSubject() = default;
		int iIdCount = 0;
		std::multimap<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::weak_ptr<EventSubject>>> listeners;
	};
}

