#pragma once

#include "displayNode.h"

namespace game {
	class VertexArrayNode
		: public DisplayNode {
	public:
		explicit VertexArrayNode(std::shared_ptr<sf::VertexArray> vertexArray);
		virtual ~VertexArrayNode();
		virtual bool containsPoint(const sf::Vector2f & point) const;
		virtual std::shared_ptr<sf::Drawable> getDrawable() override;
	private:
		std::shared_ptr<sf::VertexArray> vertexArray;
	};
}