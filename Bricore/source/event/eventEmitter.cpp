#include "eventEmitter.h"
#include "eventListener.h"
#include "event.h"
#include <algorithm>

namespace game {
	std::shared_ptr<EventListenerBase> EventEmitter::addListener(std::shared_ptr<EventListenerBase> listener) {
		return addListener(listener, std::weak_ptr<void>());
	}

	std::shared_ptr<EventListenerBase> EventEmitter::addListener(std::shared_ptr<EventListenerBase> listener, std::weak_ptr<void> trackedObject) {
		std::type_index type = listener->getEventType();
		listeners.emplace(type, std::make_pair(listener, std::move(trackedObject)));
		return listener;
	}

	void EventEmitter::emit(Event & event) {
		auto listenerRange = listeners.equal_range(typeid(event));
		std::vector<std::pair<const std::type_index, std::pair<std::shared_ptr<EventListenerBase>, std::weak_ptr<void>>>> tempListeners;
		std::copy(listenerRange.first, listenerRange.second, std::back_inserter(tempListeners));
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const std::type_index, std::pair<std::shared_ptr<EventListenerBase>, std::weak_ptr<void>>> & listenerInfo) {
			auto & trackedObject = listenerInfo.second.second;
			if ((trackedObject.owner_before(std::weak_ptr<void>{})
				|| std::weak_ptr<void>{}.owner_before(trackedObject))
				&& trackedObject.expired()) {
				removeListener(*listenerInfo.second.first);
				return;
			}

			event.accept(*listenerInfo.second.first);
		});
	}

	void EventEmitter::emit(Event && event) {
		emit(event);
	}

	void EventEmitter::removeListener(const EventListenerBase & listener) {
		auto listenerRange = listeners.equal_range(listener.getEventType());
		listeners.erase(std::find_if(listenerRange.first, listenerRange.second,
			[&](std::pair<const std::type_index, std::pair<std::shared_ptr<EventListenerBase>, std::weak_ptr<void>>> & listenerInfo) {
			return listenerInfo.second.first.get() == &listener;
		}));
	}

	void EventEmitter::removeAllListener() {
		listeners.clear();
	}
}

