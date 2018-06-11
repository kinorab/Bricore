#pragma once

#include "UIEvent.h"

namespace game {
	class SizeEvent :
		public sf::Event::SizeEvent,
		public UIEvent {
	public:
		SizeEvent(EventType type, sf::Event::SizeEvent eventData);
		virtual ~SizeEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}