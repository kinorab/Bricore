#pragma once

#include "container.h"

namespace game {
	class UIComponent
		: public game::Container {
	public:
		virtual ~UIComponent() {}
	};
}