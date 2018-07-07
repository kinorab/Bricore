#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TextEnteredEvent :
		public sf::Event::TextEvent,
		public UIEvent,
		public Cancelable {
	public:
		TextEnteredEvent(sf::Event::TextEvent eventData);
		virtual ~TextEnteredEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
	};
}