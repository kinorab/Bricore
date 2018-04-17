#pragma once

#include <memory>
#include <string>
#include <variant>
#include <SFML\Window\Event.hpp>

namespace game {
	enum class EventPhase {
		NONE,
		CAPTURING_PHASE,
		AT_TARGET,
		BUBBLING_PHASE,
	};

	class InteractiveObject;

	class Event {
	public:
		class DispatchHelper {
		public:
			explicit DispatchHelper(Event * event);
			virtual bool isPropagationStopped();
			virtual void setCurrentTarget(InteractiveObject * target);
			virtual void setPhase(EventPhase phase);
			virtual void setTarget(InteractiveObject * target);
		private:
			Event * event;
		};
		explicit Event(sf::Event::EventType type);
		Event(sf::Event::EventType type, bool bubbles, bool cancelable);
		virtual ~Event();
		virtual bool getBubbles() const;
		virtual bool getCancelable() const;
		virtual InteractiveObject * getCurrentTarget() const;
		virtual bool getDefaultPrevented() const;
		virtual EventPhase getPhase() const;
		virtual InteractiveObject * getTarget() const;
		virtual sf::Event::EventType getType() const;
		virtual void stopPropagation();
		virtual void preventDefault();
		std::variant<
			sf::Event::SizeEvent,             //< Size event parameters (Event::Resized)
			sf::Event::KeyEvent,			  //< Key event parameters (Event::KeyPressed, Event::KeyReleased)
			sf::Event::TextEvent,			  //< Text event parameters (Event::TextEntered)
			sf::Event::MouseMoveEvent,		  //< Mouse move event parameters (Event::MouseMoved)
			sf::Event::MouseButtonEvent,	  //< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
			sf::Event::MouseWheelScrollEvent, //< Mouse wheel event parameters (Event::MouseWheelScrolled)
			sf::Event::JoystickMoveEvent,	  //< Joystick move event parameters (Event::JoystickMoved)
			sf::Event::JoystickButtonEvent,	  //< Joystick button event parameters (Event::JoystickButtonPressed, Event::JoystickButtonReleased)
			sf::Event::JoystickConnectEvent,  //< Joystick (dis)connect event parameters (Event::JoystickConnected, Event::JoystickDisconnected)
			sf::Event::TouchEvent,			  //< Touch events parameters (Event::TouchBegan, Event::TouchMoved, Event::TouchEnded)
			sf::Event::SensorEvent> data;	  //< Sensor event parameters (Event::SensorChanged)
	private:
		bool bubbles;
		bool cancelable;
		InteractiveObject * currentTarget;
		bool defaultPrevented;
		EventPhase phase;
		bool propagationStopped;
		InteractiveObject * target;
		sf::Event::EventType type;
	};
}