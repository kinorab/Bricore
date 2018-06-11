#pragma once

#include "UIEvent.h"

namespace game {
	class TextEvent :
		public sf::Event::TextEvent,
		public UIEvent {
	public:
		TextEvent(EventType type, sf::Event::TextEvent eventData);
		virtual ~TextEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}