#pragma once

#include "../UIEvent.h"
#include "../cancelable.h"

namespace game {
	class KeyEvent :
		public sf::Event::KeyEvent,
		public UIEvent,
		public Cancelable {
	public:
		KeyEvent(std::type_index type, sf::Event::KeyEvent eventData);
		virtual ~KeyEvent() = default;
		virtual void accept(EventListener & visitor) override;
		class Pressed {};
		class Released {};
	};
}