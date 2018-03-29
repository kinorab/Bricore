#pragma once

#include "eventDispatcher.h"
#include <SFML/Graphics.hpp>

namespace game {
	class Sprite :
		public EventDispatcher,
		public sf::Sprite {
	public:
	};
}
