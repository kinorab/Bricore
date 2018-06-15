#pragma once

#include "../UIEvent.h"

namespace game {
	class JoystickButtonEvent :
		public sf::Event::JoystickButtonEvent,
		public UIEvent {
	public:
		JoystickButtonEvent(std::type_index type, sf::Event::JoystickButtonEvent eventData);
		virtual ~JoystickButtonEvent() = default;
		virtual void accept(EventListener & visitor) override;
		class Pressed {};
		class Released {};
	};
}