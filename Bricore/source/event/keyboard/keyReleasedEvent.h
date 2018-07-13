#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class KeyReleasedEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit KeyReleasedEvent(sf::Event::KeyEvent eventData);
		virtual ~KeyReleasedEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::KeyEvent released;
	};
}
