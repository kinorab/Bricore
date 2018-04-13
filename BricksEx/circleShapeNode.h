#pragma once

#include "displayNode.h"

namespace game {
	class CircleShapeNode
		: public DisplayNode {
	public:
		explicit CircleShapeNode(std::shared_ptr<sf::CircleShape> circleShape);
		virtual ~CircleShapeNode();
		virtual bool containsPoint(const sf::Vector2f & point) const;
		virtual std::shared_ptr<sf::Drawable> getDrawable() override;
	private:
		std::shared_ptr<sf::CircleShape> circleShape;
	};
}