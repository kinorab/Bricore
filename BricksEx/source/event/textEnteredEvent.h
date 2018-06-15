#pragma once

#include "UIEvent.h"

namespace game {
	class TextEnteredEvent :
		public sf::Event::TextEvent,
		public UIEvent {
	public:
		TextEnteredEvent(sf::Event::TextEvent eventData);
		virtual ~TextEnteredEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}