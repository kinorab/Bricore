#pragma once

#include "../interactiveObject.h"

namespace game {
	class DrawableNode
		: public InteractiveObject {
	public:
		explicit DrawableNode(std::shared_ptr<sf::Drawable> drawable);
		virtual ~DrawableNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	private:
		std::shared_ptr<sf::Drawable> drawable;
	};
}