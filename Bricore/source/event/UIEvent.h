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
		virtual EventSubject * getCurrentTarget() const;
		virtual EventPhase getPhase() const;
		virtual EventSubject * getTarget() const;
		virtual void stopPropagation();
	protected:
		UIEvent() = default;
	private:
		bool bPropagationStopped = false;
		EventPhase phase = EventPhase::NONE;
		EventSubject * currentTarget = nullptr;
		EventSubject * target = nullptr;
	};
}