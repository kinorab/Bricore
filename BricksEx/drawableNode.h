#pragma once

#include "displayNode.h"

namespace game {
	class DrawableNode
		: public DisplayNode {
	public:
		explicit DrawableNode(std::shared_ptr<sf::Drawable> drawable);
		virtual ~DrawableNode();
		virtual bool containsPoint(const sf::Vector2f & point) const;
		virtual std::shared_ptr<sf::Drawable> getDrawable() override;
	private:
		std::shared_ptr<sf::Drawable> drawable;
	};
}