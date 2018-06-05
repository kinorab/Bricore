#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class JoystickConnectEvent :
		public sf::Event::JoystickConnectEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		JoystickConnectEvent(EventType type, sf::Event::JoystickConnectEvent eventData);
		virtual ~JoystickConnectEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}