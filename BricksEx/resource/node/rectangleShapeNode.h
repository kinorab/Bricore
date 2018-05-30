#pragma once

#include "../interactiveObject.h"

namespace game {
	class RectangleShapeNode
		: public InteractiveObject {
	public:
		explicit RectangleShapeNode(std::shared_ptr<sf::RectangleShape> rectangleShape);
		virtual ~RectangleShapeNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	private:
		std::shared_ptr<sf::RectangleShape> rectangleShape;
	};
}