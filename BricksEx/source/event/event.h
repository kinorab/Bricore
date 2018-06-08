#pragma once

#include "../template/acyclicVisitable.h"
#include "eventPhase.h"
#include "eventType.h"
#include <SFML\Window\Event.hpp>
#include <memory>
#include <string>
#include <variant>

namespace game {
	class EventSubject;
	class EventListener;

	class Event :
		public AcyclicVisitable<EventListener> {
		friend class DispatchHelper;
	public:
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
		Event(EventType type, bool bubbles, bool cancelable);
		virtual void visitFailedHandler() override;
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