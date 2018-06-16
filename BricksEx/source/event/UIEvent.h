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
		virtual EventSubject * getCurrentTarget() const;
		virtual EventPhase getPhase() const;
		virtual EventSubject * getTarget() const;
		virtual std::type_index getType() const;
		virtual void stopPropagation();
	protected:
		UIEvent(std::type_index type, bool bubbles);
	private:
		bool bubbles;
		EventSubject * currentTarget;
		EventPhase phase = EventPhase::NONE;
		bool propagationStopped = false;
		EventSubject * target;
		std::type_index type;
	};
}