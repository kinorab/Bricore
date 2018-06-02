#pragma once

#include "../event/eventType.h"
#include <map>
#include <functional>

namespace game {
	class Event;

	class EventSubject {
	public:
		EventSubject();
		virtual ~EventSubject();
		virtual int addEventListener(EventType type, std::function<void(Event *)> callback);
		virtual bool dispatchEvent(Event * event);
		virtual void removeEventListener(int id);
	private:
		struct EventListener {
			EventType type;
			std::function<void(Event *)> callback;
		};
		std::map<int, EventListener> listeners;
		int idCount;
	};
}

