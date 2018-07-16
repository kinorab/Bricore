#pragma once
#include "../event/text/textEvent.h"
#include <SFML/Window/Event.hpp>
#include <memory>

namespace game {
	class Container;
	class TextHandler {
	public:
		TextHandler() noexcept;
		void handle(const sf::Event & event, Container & thing);
		virtual ~TextHandler() = default;
	private:
		void handleTextEntered(const sf::Event & event, Container & thing);
	};
}