#include "vertexArrayNode.h"

namespace game {
	VertexArrayNode::VertexArrayNode(std::shared_ptr<sf::VertexArray> vertexArray) {
		this->vertexArray = std::move(vertexArray);
	}

	VertexArrayNode::~VertexArrayNode() {

	}

	bool VertexArrayNode::containsPoint(const sf::Vector2f &) const {
		return false;
	}

	std::shared_ptr<sf::Drawable> VertexArrayNode::getDrawable() const	{
		return vertexArray;
	}
}
