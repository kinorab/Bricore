#pragma once

#include "event.h"

namespace game {
	class DefaultEvent :
		public Event {
	public:
		DefaultEvent(std::string type, bool bubbles, bool cancelable);
		virtual ~DefaultEvent() override;
		virtual bool getBubbles() const override;
		virtual bool getCancelable() const override;
		virtual EventDispatcher * getCurrentTarget() const override;
		virtual bool getDefaultPrevented() const override;
		virtual EventPhase getEventPhase() const override;
		virtual EventDispatcher * getTarget() const override;
		virtual std::string getType() const override;
		virtual void stopPropagation() override;
		virtual void preventDefault() override;
	private:
		EventPhase eventPhase;
		bool bubbles;
		bool cancelable;
		bool defaultPrevented;
		bool propagationStopped;
		std::string type;
	};
}