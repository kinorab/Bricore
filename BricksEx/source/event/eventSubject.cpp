#include "eventSubject.h"
#include "eventListener.h"
#include "event.h"
#include <algorithm>

namespace game {
	int EventSubject::addListener(std::shared_ptr<EventListenerBase> listener) {
		return addListener(listener, nullptr);
	}

	int EventSubject::addListener(std::shared_ptr<EventListenerBase> listener, std::shared_ptr<EventSubject> trackedSubject) {
		listeners.emplace(listener->getEventType(), std::make_tuple(idCount, std::move(listener), std::move(trackedSubject)));
		int returnId = idCount;
		idCount += 1;
		return returnId;
	}

	void EventSubject::dispatchEvent(Event & event) {
		auto listenerRange = listeners.equal_range(typeid(event));
		std::vector<std::pair<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::shared_ptr<EventSubject>>>> tempListeners;
		std::copy(listenerRange.first, listenerRange.second, std::back_inserter(tempListeners));
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::shared_ptr<EventSubject>>> & listener) {
			if (std::get<2>(listener.second).use_count() == 1) {
				removeListener(listener.first, std::get<0>(listener.second));
				return;
			}

			event.accept(*std::get<1>(listener.second));
		});
	}

	void EventSubject::removeListener(std::type_index eventType, int id) {
		auto listenerRange = listeners.equal_range(eventType);
		listeners.erase(std::find_if(listenerRange.first, listenerRange.second,
			[&](std::pair<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::shared_ptr<EventSubject>>> & listener) {
			return std::get<0>(listener.second) == id;
		}));
	}
}

