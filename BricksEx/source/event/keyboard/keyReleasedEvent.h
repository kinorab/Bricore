#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class KeyReleasedEvent :
		public sf::Event::KeyEvent,
		public UIEvent,
		public Cancelable {
	public:
		KeyReleasedEvent(sf::Event::KeyEvent eventData);
		virtual ~KeyReleasedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}
