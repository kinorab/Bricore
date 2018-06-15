#pragma once

#include "event.h"
#include "eventPhase.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class EventSubject;

	class UIEvent :
		public Event {
		friend class DispatchHelper;
	public:
		virtual ~UIEvent() = default;
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual EventSubject * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual EventSubject * getTarget() const;
		virtual std::type_index getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
	protected:
		UIEvent(std::type_index type, bool bubbles, bool cancelable);
	private:
		bool bubbles;
		bool cancelable;
		EventSubject * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		EventSubject * target;
		std::type_index type;
	};
}