#pragma once

#include "interactiveObject.h"

namespace sf {
	class CircleShape;
}

namespace game {
	class CircleShapeNode
		: public InteractiveObject {
	public:
		explicit CircleShapeNode(std::shared_ptr<sf::CircleShape> circleShape);
		virtual ~CircleShapeNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	private:
		std::shared_ptr<sf::CircleShape> circleShape;
	};
}