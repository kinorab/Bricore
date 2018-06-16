#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class TouchEvent :
		public sf::Event::TouchEvent,
		public UIEvent,
		public Cancelable {
	public:
		TouchEvent(std::type_index type, sf::Event::TouchEvent eventData);
		virtual ~TouchEvent() = default;
		virtual void accept(EventListener & visitor) override;
		class Began {};
		class Moved {};
		class Ended {};
	};
}