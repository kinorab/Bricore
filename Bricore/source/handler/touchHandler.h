#pragma once
#include "../event/touch/touchEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class TouchHandler {
	public:
		TouchHandler() noexcept;
		void handle(const sf::Event & event, Container & thing);
		virtual ~TouchHandler() = default;
	private:
		void handleTouchBegan(const sf::Event & event, Container & thing);
		void handleTouchMoved(const sf::Event & event, Container & thing);
		void handleTouchEnded(const sf::Event & event, Container & thing);
	};
}