#include "eventSubject.h"
#include "eventListener.h"
#include "event.h"
#include <algorithm>

namespace game {
	int EventSubject::addListener(std::shared_ptr<EventListenerBase> listener) {
		listeners.emplace(listener->getEventType(), std::pair<const int, std::shared_ptr<EventListenerBase>>(idCount, std::move(listener)));
		int returnId = idCount;
		idCount += 1;
		return returnId;
	}

	void EventSubject::dispatchEvent(Event & event) {
		auto listenerRange = listeners.equal_range(typeid(event));
		std::vector<std::pair<const std::type_index, std::pair<const int, std::shared_ptr<EventListenerBase>>>> tempListeners;
		std::copy(listenerRange.first, listenerRange.second, std::back_inserter(tempListeners));
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const std::type_index, std::pair<const int, std::shared_ptr<EventListenerBase>>> & listener) {
			event.accept(*listener.second.second);
		});
	}

	void EventSubject::removeListener(std::type_index eventType, int id) {
		auto listenerRange = listeners.equal_range(eventType);
		listeners.erase(std::find_if(listenerRange.first, listenerRange.second,
			[&](std::pair<const std::type_index, std::pair<const int, std::shared_ptr<EventListenerBase>>> & listener) {
			return listener.second.first == id;
		}));
	}
}

