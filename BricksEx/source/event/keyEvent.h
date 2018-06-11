#pragma once

#include "UIEvent.h"

namespace game {
	class KeyEvent :
		public sf::Event::KeyEvent,
		public UIEvent {
	public:
		KeyEvent(EventType type, sf::Event::KeyEvent eventData);
		virtual ~KeyEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}