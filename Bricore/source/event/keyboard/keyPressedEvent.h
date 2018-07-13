#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class KeyPressedEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit KeyPressedEvent(sf::Event::KeyEvent eventData);
		virtual ~KeyPressedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::KeyEvent pressed;
	};
}
