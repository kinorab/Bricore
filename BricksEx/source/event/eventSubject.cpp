#include "eventSubject.h"
#include "event.h"
#include "dispatchHelper.h"

namespace game {
	EventSubject::EventSubject() :
		idCount(0) {
	}

	EventSubject::~EventSubject() {
	}

	int EventSubject::addEventListener(EventType type, std::function<void(Event *)> callback) {
		listeners[idCount] = EventListener{ type, callback };
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

		std::map<int, EventListener> tempListeners = listeners;
		std::for_each(tempListeners.begin(), tempListeners.end(),
			[&](const std::pair<const int, EventListener> & listener) {
			if (event->getType() == listener.second.type) {
				listener.second.callback(event);
			}
		});
	}

	void EventSubject::removeEventListener(int id) {
		listeners.erase(std::find_if(listeners.begin(), listeners.end(),
			[&](std::pair<const int, EventListener> & listener) {
			return listener.first == id;
		}));
	}
}

