#pragma once

#include "interactiveObject.h"

namespace game {
	class VertexArrayNode
		: public InteractiveObject {
	public:
		explicit VertexArrayNode(std::shared_ptr<sf::VertexArray> vertexArray);
		virtual ~VertexArrayNode();
		virtual bool containsPoint(const sf::Vector2f & point) const override;
		virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	private:
		std::shared_ptr<sf::VertexArray> vertexArray;
	};
}