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

	class Container;

	class Event {
	public:
		class DispatchHelper {
		public:
			explicit DispatchHelper(Event * event);
			virtual bool isPropagationStopped();
			virtual void setCurrentTarget(Container * target);
			virtual void setPhase(EventPhase phase);
			virtual void setTarget(Container * target);
		private:
			Event * event;
		};
		explicit Event(std::string type);
		Event(std::string type, bool bubbles, bool cancelable);
		virtual ~Event();
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual Container * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual Container * getTarget() const;
		virtual std::string getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
	private:
		bool bubbles;
		bool cancelable;
		Container * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		Container * target;
		std::string type;
	};
}