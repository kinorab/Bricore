#pragma once

#include "../visitable.h"
#include "eventListener.h"
#include "eventPhase.h"
#include "eventType.h"
#include <SFML\Window\Event.hpp>
#include <memory>
#include <string>
#include <variant>

namespace game {
	class EventSubject;

	class Event :
		public Visitable<EventListener> {
		friend class DispatchHelper;
	public:
		Event(EventType type, bool bubbles, bool cancelable);
		virtual ~Event() = default;
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual EventSubject * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual EventSubject * getTarget() const;
		virtual EventType getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
	protected:
	private:
		bool bubbles;
		bool cancelable;
		EventSubject * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		EventSubject * target;
		EventType type;
	};
}