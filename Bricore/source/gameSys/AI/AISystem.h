#pragma once
#include "../system.h"

namespace sf {
	class Event;
}
namespace game {
	class AISystem :
		public System {
	public:
		AISystem();
		virtual void handle(const sf::Event * const event) = 0;
		virtual ~AISystem();
	};
}