#include "eventDispatcher.h"
#include <algorithm>

namespace game {
	struct EventDispatcher::EventListener {
		std::string type;
		std::function<void(Event *)> callback;
		bool useCapture;
	};

	EventDispatcher::EventDispatcher() {

	}

	EventDispatcher::~EventDispatcher() {

	}

	void EventDispatcher::addEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture) {
		removeEventListener(type, callback, useCapture);
		listeners.push_back(EventListener{ type, callback, useCapture });
	}
	
	bool EventDispatcher::dispatchEvent(DefaultEvent * event) {
		DefaultEvent::DispatchHelper helper(event);
		helper.setEventPhase(EventPhase::CAPTURING_PHASE);
		return false;
	}
	
	void EventDispatcher::removeEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture) {
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
			[&](EventListener & listener) {
			return listener.type == type
				&& *listener.callback.target<void(Event *)>() == *callback.target<void(Event *)>()
				&& listener.useCapture == useCapture;
		}));
	}
}
