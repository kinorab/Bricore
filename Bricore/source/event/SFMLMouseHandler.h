#pragma once

#include "../interact/container.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class SFMLMouseHandler {
	public:
		explicit SFMLMouseHandler(const sf::Vector2i clientSize);
		virtual ~SFMLMouseHandler() = default;
		virtual void handle(const sf::Event & event, Container & thing);
	private:
		virtual void handleMouseButtonPressed(const sf::Event & event, Container & thing);
		virtual void handleMouseButtonReleased(const sf::Event & event, Container & thing);
		virtual void handleMouseLeft(const sf::Event & event, Container & thing);
		virtual void handleMouseMove(const sf::Event & event, Container & thing);
		const sf::Vector2i clientSize;
		std::shared_ptr<InteractiveObject> previousContactNode;
	};
}
