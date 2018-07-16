#pragma once
#include "../event/joystick/joystickEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class JoystickHandler {
	public:
		explicit JoystickHandler() noexcept;
		void handler(const sf::Event & event, Container & thing);
		virtual ~JoystickHandler() = default;

	private:
		void handleJoystickConnected(const sf::Event & event, Container & thing);
		void handleJoystickDisconnected(const sf::Event & event, Container & thing);
		void handleJoystickMoved(const sf::Event & event, Container & thing);
		void handleJoystickPressed(const sf::Event & event, Container & thing);
		void handleJoystickReleased(const sf::Event & event, Container & thing);
	};
}