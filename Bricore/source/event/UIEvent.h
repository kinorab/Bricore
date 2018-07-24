#pragma once

#include "event.h"
#include "eventPhase.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class EventEmitter;

	class UIEvent :
		public Event {
		friend class DispatchHelper;
	public:
		virtual ~UIEvent() = default;
		virtual EventEmitter * getCurrentTarget() const;
		virtual EventPhase getPhase() const;
		virtual EventEmitter * getTarget() const;
		virtual void stopPropagation();
	protected:
		UIEvent() = default;
	private:
		bool bPropagationStopped = false;
		EventPhase phase = EventPhase::NONE;
		EventEmitter * currentTarget = nullptr;
		EventEmitter * target = nullptr;
	};
}