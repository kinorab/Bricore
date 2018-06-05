#include "eventSubject.h"
#include "event.h"
#include "dispatchHelper.h"

namespace game {
	EventSubject::EventSubject() :
		idCount(0) {
	}

	int EventSubject::addListener(EventType eventType, std::shared_ptr<EventListener> listener) {
		listeners[idCount] = std::make_pair(eventType, std::move(listener));
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

		auto tempListeners = listeners;
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](std::pair<const int, std::pair<EventType, std::shared_ptr<EventListener>>> & listener) {
			if (event->getType() == listener.second.first) {
				event->accept(listener.second.second.get());
			}
		});
	}

	void EventSubject::removeListener(int id) {
		listeners.erase(std::find_if(listeners.begin(), listeners.end(),
			[&](std::pair<const int, std::pair<EventType, std::shared_ptr<EventListener>>> & listener) {
			return listener.first == id;
		}));
	}
}

