#include "spriteNode.h"

namespace game {
	SpriteNode::SpriteNode(std::shared_ptr<sf::Sprite> sprite) {
		this->sprite = std::move(sprite);
	}

	SpriteNode::~SpriteNode() {

	}

	bool SpriteNode::containsPoint(const sf::Vector2f & point) const {
		return sprite->getGlobalBounds().contains(getTransform().getInverse().transformPoint(point));
	}

	std::shared_ptr<sf::Drawable> SpriteNode::getDrawable() const {
		return sprite;
	}
}
