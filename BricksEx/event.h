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

	class DisplayNode;

	class Event {
	public:
		class DispatchHelper {
		public:
			explicit DispatchHelper(Event * event);
			virtual bool isPropagationStopped();
			virtual void setCurrentTarget(DisplayNode * target);
			virtual void setPhase(EventPhase phase);
			virtual void setTarget(DisplayNode * target);
		private:
			Event * event;
		};
		explicit Event(std::string type);
		Event(std::string type, bool bubbles, bool cancelable);
		virtual ~Event();
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual DisplayNode * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual DisplayNode * getTarget() const;
		virtual std::string getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
	private:
		bool bubbles;
		bool cancelable;
		DisplayNode * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		DisplayNode * target;
		std::string type;
	};
}