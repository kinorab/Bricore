#pragma once

#include "Event.h"
#include <functional>
#include <vector>

namespace game {
	class EventDispatcher {
	public:
		EventDispatcher();
		virtual ~EventDispatcher();
		virtual void addEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture);
		virtual bool dispatchEvent(Event * event);
		virtual void removeEventListener(std::string type, std::function<void(Event *)> callback, bool useCapture);
	private:
		struct EventListener;
		std::vector<EventListener> listeners;
	};
}
