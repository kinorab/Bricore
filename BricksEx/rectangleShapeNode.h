#pragma once

#include "displayNode.h"

namespace game {
	class RectangleShapeNode
		: public DisplayNode {
	public:
		explicit RectangleShapeNode(std::shared_ptr<sf::RectangleShape> rectangleShape);
		virtual ~RectangleShapeNode();
		virtual bool containsPoint(const sf::Vector2f & point) const;
		virtual std::shared_ptr<sf::Drawable> getDrawable() override;
	private:
		std::shared_ptr<sf::RectangleShape> rectangleShape;
	};
}