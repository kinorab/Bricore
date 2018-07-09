#pragma once

#include "../interact/container.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class SFMLMouseHandler {
	public:
		explicit SFMLMouseHandler(const sf::Vector2i clientSize);
		virtual ~SFMLMouseHandler() = default;
		virtual void handle(const sf::Event & event, Container & target, const bool isTargetFullScreen);
	private:
		virtual void handleMouseButtonPressed(const sf::Event & event, Container & target);
		virtual void handleMouseButtonReleased(const sf::Event & event, Container & target);
		virtual void handleMouseLeft(const sf::Event & event, Container & target, const bool isTargetFullScreen);
		virtual void handleMouseMove(const sf::Event & event, Container & target, const bool isTargetFullScreen);
		const sf::Vector2i clientSize;
		std::shared_ptr<InteractiveObject> previousContactNode;
	};
}
