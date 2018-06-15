#pragma once

#include "UIEvent.h"

namespace game {
	class ResizedEvent :
		public sf::Event::SizeEvent,
		public UIEvent {
	public:
		ResizedEvent(sf::Event::SizeEvent eventData);
		virtual ~ResizedEvent() = default;
		virtual void accept(EventListener & visitor) override;
	};
}