#pragma once
#include "../event/mouse/mouseEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class InteractiveObject;
	class MouseHandler {
	public:
		MouseHandler();
		virtual void handle(const sf::Event & event, Container & target);
		virtual ~MouseHandler() = default;

	private:
		virtual void handleMouseButtonPressed(const sf::Event & event, Container & target);
		virtual void handleMouseButtonReleased(const sf::Event & event, Container & target);
		virtual void handleMouseLeft(const sf::Event & event, Container & target);
		virtual void handleMouseMove(const sf::Event & event, Container & target);
		std::shared_ptr<InteractiveObject> previousContactNode;
	};
}
