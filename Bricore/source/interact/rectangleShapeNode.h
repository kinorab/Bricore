#pragma once

#include "interactiveObject.h"

namespace sf {
	class RectangleShape;
}

namespace game {
	class RectangleShapeNode
		: public InteractiveObject {
	public:
		explicit RectangleShapeNode(std::shared_ptr<sf::RectangleShape> rectangleShape);
		virtual ~RectangleShapeNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	protected:
		std::shared_ptr<sf::RectangleShape> rectangleShape;
	};
}