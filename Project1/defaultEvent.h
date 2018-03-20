#pragma once

#include "event.h"
#include <memory>

namespace game {
	class DefaultEvent :
		public Event {
	public:
		class DispatchHelper {
		public:
			explicit DispatchHelper(DefaultEvent * event);
			virtual void setEventPhase(EventPhase phase);
		private:
			DefaultEvent * event;
		};
		DefaultEvent(std::string type, bool bubbles, bool cancelable);
		virtual ~DefaultEvent() override;
		virtual bool getBubbles() const override;
		virtual bool getCancelable() const override;
		virtual EventDispatcher * getCurrentTarget() const override;
		virtual bool getDefaultPrevented() const override;
		virtual EventPhase getPhase() const override;
		virtual EventDispatcher * getTarget() const override;
		virtual std::string getType() const override;
		virtual void stopPropagation() override;
		virtual void preventDefault() override;
	private:
		EventPhase phase;
		bool bubbles;
		bool cancelable;
		bool defaultPrevented;
		bool propagationStopped;
		std::string type;
	};
}