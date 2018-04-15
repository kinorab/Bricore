#pragma once

#include <memory>
#include <string>
#include <SFML\Window\Event.hpp>

namespace game {
	enum class EventPhase {
		NONE,
		CAPTURING_PHASE,
		AT_TARGET,
		BUBBLING_PHASE,
	};

	class InteractiveObject;

	class Event
		:public sf::Event {
	public:
		class DispatchHelper {
		public:
			explicit DispatchHelper(Event * event);
			virtual bool isPropagationStopped();
			virtual void setCurrentTarget(InteractiveObject * target);
			virtual void setPhase(EventPhase phase);
			virtual void setTarget(InteractiveObject * target);
		private:
			Event * event;
		};
		explicit Event(sf::Event::EventType type);
		Event(sf::Event::EventType type, bool bubbles, bool cancelable);
		virtual ~Event();
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual InteractiveObject * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual InteractiveObject * getTarget() const;
		virtual sf::Event::EventType getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
	private:
		bool bubbles;
		bool cancelable;
		InteractiveObject * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		InteractiveObject * target;
		using sf::Event::type;
	};
}