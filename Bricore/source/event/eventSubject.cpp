#include "eventSubject.h"
#include "eventListener.h"
#include "event.h"
#include <algorithm>

namespace game {
	int EventSubject::addListener(std::shared_ptr<EventListenerBase> listener) {
		return addListener(listener, std::weak_ptr<EventSubject>());
	}

	int EventSubject::addListener(std::shared_ptr<EventListenerBase> listener, std::weak_ptr<EventSubject> trackedSubject) {
		listeners.emplace(listener->getEventType(), std::make_tuple(iIdCount, std::move(listener), std::move(trackedSubject)));
		int returnId = iIdCount;
		iIdCount += 1;
		return iIdCount;
	}

	void EventSubject::dispatchEvent(Event & event) {
		auto listenerRange = listeners.equal_range(typeid(event));
		std::vector<std::pair<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::weak_ptr<EventSubject>>>> tempListeners;
		std::copy(listenerRange.first, listenerRange.second, std::back_inserter(tempListeners));
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::weak_ptr<EventSubject>>> & listener) {
			auto & lockedSubject = std::get<2>(listener.second);
			if ((lockedSubject.owner_before(std::weak_ptr<EventSubject>{})
				|| std::weak_ptr<EventSubject>{}.owner_before(lockedSubject))
				&& lockedSubject.expired()) {
				removeListener(listener.first, std::get<0>(listener.second));
				return;
			}

			event.accept(*std::get<1>(listener.second));
		});
	}

	void EventSubject::dispatchEvent(Event && event) {
		dispatchEvent(event);
	}

	void EventSubject::removeListener(std::type_index eventType, int id) {
		auto listenerRange = listeners.equal_range(eventType);
		listeners.erase(std::find_if(listenerRange.first, listenerRange.second,
			[&](std::pair<const std::type_index, std::tuple<const int, std::shared_ptr<EventListenerBase>, std::weak_ptr<EventSubject>>> & listener) {
			return std::get<0>(listener.second) == id;
		}));
	}

	int EventSubject::getIdCount() const {
		return iIdCount;
	}
}

