#include "drawableNode.h"

namespace game {
	DrawableNode::DrawableNode(std::shared_ptr<sf::Drawable> drawable) {
		this->drawable = std::move(drawable);
	}

	DrawableNode::~DrawableNode() {

	}

	bool DrawableNode::containsPoint(const sf::Vector2f & point) const {
		return false;
	}

	std::shared_ptr<sf::Drawable> DrawableNode::getDrawable() const {
		return drawable;
	}
}
