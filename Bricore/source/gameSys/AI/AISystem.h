#pragma once
#include "../system.h"

namespace sf {
	class Event;
}
namespace game {
	class AISystem :
		public System {
	public:
		virtual ~AISystem();

	protected:
		AISystem();
	};
}