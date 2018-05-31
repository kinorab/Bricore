#include "rectangleShapeNode.h"

namespace game {
	RectangleShapeNode::RectangleShapeNode(std::shared_ptr<sf::RectangleShape> rectangleShape) {
		this->rectangleShape = std::move(rectangleShape);
	}

	RectangleShapeNode::~RectangleShapeNode() {
		
	}

	bool RectangleShapeNode::containsPoint(const sf::Vector2f & point) const {
		return rectangleShape->getGlobalBounds().contains(getTransform().getInverse().transformPoint(point));
	}

	std::shared_ptr<sf::Drawable> RectangleShapeNode::getDrawable() const {
		return rectangleShape;
	}
}
