#pragma once

#include "../visitor.h"
#include <SFML\Window\Event.hpp>

namespace game {
	class SizeEvent;
	class KeyEvent;
	class TextEvent;
	class MouseMoveEvent;
	class MouseButtonEvent;
	class MouseWheelScrollEvent;
	class JoystickMoveEvent;
	class JoystickButtonEvent;
	class JoystickConnectEvent;
	class TouchEvent;
	class SensorEvent;

	class EventListener : 
		public Visitor<SizeEvent,
		KeyEvent,
		TextEvent,
		MouseMoveEvent,
		MouseButtonEvent,
		MouseWheelScrollEvent,
		JoystickMoveEvent,
		JoystickButtonEvent,
		JoystickConnectEvent,
		TouchEvent,
		SensorEvent> {
	public:
		virtual ~EventListener() = default;
	private:
		virtual void visitFailedHandler() override;
	};
}
