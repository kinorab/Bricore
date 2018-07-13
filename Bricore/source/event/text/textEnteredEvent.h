#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TextEnteredEvent :
		public UIEvent,
		public Cancelable {
	public:
		explicit TextEnteredEvent(sf::Event::TextEvent eventData);
		virtual ~TextEnteredEvent() = default;
		virtual void accept(EventListenerBase & visitor) override;
		sf::Event::TextEvent entered;
	};
}