#include "eventSubject.h"
#include "event.h"
#include "dispatchHelper.h"

namespace game {
	EventSubject::EventSubject() :
		idCount(0) {
	}

	int EventSubject::addListener(EventType eventType, std::shared_ptr<EventListener> listener) {
		listeners.emplace(eventType, std::pair<const int, std::shared_ptr<EventListener>>(idCount, std::move(listener)));
		int returnId = idCount;
		idCount += 1;
		return returnId;
	}

	void EventSubject::dispatchEvent(Event * event) {
		DispatchHelper helper(event);
		helper.setCurrentTarget(this);

		if (event->getPhase() == EventPhase::NONE) {
			helper.setTarget(this);
			helper.setPhase(EventPhase::AT_TARGET);
		}

		auto listenerRange = listeners.equal_range(event->getType());
		std::vector<std::pair<const EventType, std::pair<const int, std::shared_ptr<EventListener>>>> tempListeners;
		std::copy(listenerRange.first, listenerRange.second, std::back_inserter(tempListeners));
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const EventType, std::pair<const int, std::shared_ptr<EventListener>>> & listener) {
			event->accept(listener.second.second.get());
		});
	}

	void EventSubject::removeListener(EventType eventType, int id) {
		auto listenerRange = listeners.equal_range(eventType);
		listeners.erase(std::find_if(listenerRange.first, listenerRange.second,
			[&](std::pair<const EventType, std::pair<const int, std::shared_ptr<EventListener>>> & listener) {
			return listener.second.first == id;
		}));
	}
}

