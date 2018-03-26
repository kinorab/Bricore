#pragma once

#include <memory>
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
		class DispatchHelper {
		public:
			explicit DispatchHelper(Event * event);
			virtual void setCurrentTarget(EventDispatcher * target);
			virtual void setPhase(EventPhase phase);
			virtual void setTarget(EventDispatcher * target);
		private:
			Event * event;
		};
		Event(std::string type, bool bubbles, bool cancelable);
		virtual ~Event();
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual EventDispatcher * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual EventDispatcher * getTarget() const;
		virtual std::string getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
	private:
		bool bubbles;
		bool cancelable;
		EventDispatcher * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		EventDispatcher * target;
		std::string type;
	};
}