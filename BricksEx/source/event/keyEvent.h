#pragma once

#include "event.h"
#include "../visitable.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class KeyEvent :
		public sf::Event::KeyEvent,
		public virtual Event,
		public virtual Visitable<EventListener> {
	public:
		KeyEvent(EventType type, sf::Event::KeyEvent eventData);
		virtual ~KeyEvent() = default;
		virtual void accept(EventListener * visitor) override;
	};
}