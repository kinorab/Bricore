#pragma once

#include "../common.h"
#include <map>
#include <functional>

namespace game {
	class Event;
	class EventListenerBase;

	class EventEmitter {
	public:
		virtual ~EventEmitter() = default;
		virtual std::shared_ptr<EventListenerBase> addListener(std::shared_ptr<EventListenerBase> listener);
		virtual std::shared_ptr<EventListenerBase> addListener(std::shared_ptr<EventListenerBase> listener, std::weak_ptr<void> trackedObject);
		virtual void emit(Event & event);
		virtual void emit(Event && event);
		virtual void removeListener(const EventListenerBase & listener);
		virtual void removeAllListener();
	protected:
		std::multimap<const std::type_index, std::pair<std::shared_ptr<EventListenerBase>, std::weak_ptr<void>>> listeners;
	};
}

