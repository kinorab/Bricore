#pragma once

#include "eventDispatcher.h"
#include <SFML/Graphics.hpp>

namespace game {
	class Sprite :
		public EventDispatcher,
		public sf::Sprite {
	public:
		virtual void addEventListener() override;
		virtual bool hasEventListener() override;
		virtual void removeEventListener() override;
	};
}
