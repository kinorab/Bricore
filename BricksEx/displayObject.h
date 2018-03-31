#pragma once

#include "eventDispatcher.h"
#include <SFML/Graphics.hpp>

namespace game {
	class Container;
	class DisplayObject :
		public EventDispatcher {
	public:
		explicit DisplayObject(sf::Drawable * content);
		virtual void setParent(std::weak_ptr<Container> parent);
		virtual std::weak_ptr<Container> getParent();
	private:
		std::weak_ptr<Container> parent;
		std::unique_ptr<sf::Drawable> content;
	};
}
