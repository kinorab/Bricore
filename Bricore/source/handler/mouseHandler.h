#pragma once
#include "../event/mouse/mouseEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace sf {
	class RenderWindow;
}

namespace game {
	class Container;
	class InteractiveObject;
	class MouseHandler {
	public:
		explicit MouseHandler(const std::shared_ptr<const sf::RenderWindow> window) noexcept;
		virtual void handle(const sf::Event & event, Container & target);
		virtual ~MouseHandler() = default;

	private:
		void handleMouse(const sf::Event & event, Container & target);
		void handleMouseMove(const sf::Event & event, Container & target);
		void handleMouseButtonPressed(const sf::Event & event, Container & target);
		void handleMouseButtonReleased(const sf::Event & event, Container & target);
		std::shared_ptr<InteractiveObject> previousContactNode;
		std::shared_ptr<const sf::RenderWindow> c_window;
	};
}
