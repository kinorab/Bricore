#include "circleShapeNode.h"

namespace game {
	CircleShapeNode::CircleShapeNode(std::shared_ptr<sf::CircleShape> circleShape) {
		this->circleShape = std::move(circleShape);
	}

	CircleShapeNode::~CircleShapeNode() {

	}

	bool CircleShapeNode::containsPoint(const sf::Vector2f & point) const {
		sf::Vector2f displacement = circleShape->getPosition() - point;
		if (pow(displacement.x, 2) + pow(displacement.y, 2) <= pow(circleShape->getRadius(), 2)) {
			return true;
		}

		return false;
	}

	std::shared_ptr<sf::Drawable> CircleShapeNode::getDrawable() {
		return circleShape;
	}
}
