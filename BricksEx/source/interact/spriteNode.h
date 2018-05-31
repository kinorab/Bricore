#pragma once

#include "interactiveObject.h"

namespace game {
	class SpriteNode
		: public InteractiveObject {
	public:
		explicit SpriteNode(std::shared_ptr<sf::Sprite> sprite);
		virtual ~SpriteNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	private:
		std::shared_ptr<sf::Sprite> sprite;
	};
}