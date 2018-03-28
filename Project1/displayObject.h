#pragma once

#include "eventDispatcher.h"
#include <SFML/Graphics.hpp>

namespace game {
	class Container;
	template<class T>
	class DisplayObject :
		public EventDispatcher,
		public T {
		using T::T;
	public:
	private:
		std::weak_ptr<Container> parent;
	};
}
