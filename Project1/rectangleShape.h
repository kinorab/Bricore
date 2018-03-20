#pragma once

#include "eventDispatcher.h"
#include <SFML/Graphics.hpp>

namespace game {
	class RectangleShape :
		public EventDispatcher,
		public sf::RectangleShape {
	public:
		explicit RectangleShape(const sf::Vector2f & size);
	};
}
