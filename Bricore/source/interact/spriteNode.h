#pragma once

#include "interactiveObject.h"

namespace sf {
	class Sprite;
}

namespace game {
	class SpriteNode
		: public InteractiveObject {
	public:
		explicit SpriteNode(std::shared_ptr<sf::Sprite> sprite);
		virtual ~SpriteNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	protected:
		std::shared_ptr<sf::Sprite> sprite;
	};
}