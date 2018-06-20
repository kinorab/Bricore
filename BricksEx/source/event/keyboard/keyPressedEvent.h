#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class KeyPressedEvent :
		public sf::Event::KeyEvent,
		public UIEvent,
		public Cancelable {
	public:
		KeyPressedEvent(sf::Event::KeyEvent eventData);
		virtual ~KeyPressedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
