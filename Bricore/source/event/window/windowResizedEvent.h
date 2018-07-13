#pragma once
#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class WindowResizedEvent :
		public UIEvent
		, public Cancelable {
	public:
		explicit WindowResizedEvent(sf::Event::SizeEvent eventData);
		virtual void accept(EventListenerBase & visitor) override;
		virtual ~WindowResizedEvent() = default;
		sf::Event::SizeEvent resized;
	};
}