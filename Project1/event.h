#pragma once

#include <string>

namespace game {
	enum class EventPhase {
		NONE,
		CAPTURING_PHASE,
		AT_TARGET,
		BUBBLING_PHASE,
	};

	class EventDispatcher;

	class Event {
	public:
		virtual ~Event() {}
		virtual bool getBubbles() const = 0;
		virtual bool getCancelable() const = 0;
	    virtual EventDispatcher * getCurrentTarget() const = 0;
		virtual bool getDefaultPrevented() const = 0;
		virtual EventPhase getEventPhase() const = 0;
	    virtual EventDispatcher * getTarget() const = 0;
		virtual std::string getType() const = 0;
		virtual void stopPropagation() = 0;
		virtual void preventDefault() = 0;
	};
}