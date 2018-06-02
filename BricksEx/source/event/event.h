#pragma once

#include "eventType.h"
#include "eventPhase.h"
#include <SFML\Window\Event.hpp>
#include <memory>
#include <string>
#include <variant>

namespace game {
	class InteractiveObject;

	class Event {
		friend class DispatchHelper;
	public:
		explicit Event(EventType type);
		Event(EventType type, bool bubbles, bool cancelable);
		virtual ~Event();
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual InteractiveObject * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual InteractiveObject * getTarget() const;
		virtual EventType getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
		using dataType = std::variant<
			sf::Event::SizeEvent,
			sf::Event::KeyEvent,
			sf::Event::TextEvent,
			sf::Event::MouseMoveEvent,
			sf::Event::MouseButtonEvent,
			sf::Event::MouseWheelScrollEvent,
			sf::Event::JoystickMoveEvent,
			sf::Event::JoystickButtonEvent,
			sf::Event::JoystickConnectEvent,
			sf::Event::TouchEvent,
			sf::Event::SensorEvent>;
		dataType data;
	private:
		bool bubbles;
		bool cancelable;
		InteractiveObject * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		InteractiveObject * target;
		EventType type;
	};
}