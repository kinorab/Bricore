#include "displayObject.h"

namespace game {
	DisplayObject::DisplayObject(sf::Drawable * content)
		: content(content) {
	}

	void DisplayObject::setParent(std::weak_ptr<Container> parent) {
		this->parent = std::move(parent);
	}

	std::weak_ptr<Container> DisplayObject::getParent() {
		return parent;
	}
}